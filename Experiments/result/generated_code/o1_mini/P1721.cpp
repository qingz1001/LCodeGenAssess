#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 3000
#define MAX_DIGITS 6000 + 20

typedef struct {
    char digits[MAX_DIGITS + 1];
    int length;
} BigNumber;

// Initialize BigNumber with h * 10^(2p)
void initBigNumber(BigNumber *num, long long h, int two_p) {
    // Initialize all digits to '0'
    for(int i=0;i<two_p;i++) num->digits[i] = '0';
    // Convert h to string
    char temp[25];
    sprintf(temp, "%lld", h);
    int len = strlen(temp);
    // Place h at the beginning
    for(int i=0;i<len;i++) num->digits[i] = temp[i];
    // Fill the rest with '0'
    for(int i=len;i<two_p + len;i++) {
        num->digits[i] = '0';
    }
    num->length = two_p + len;
    // Remove leading zeros
    int start = 0;
    while(start < num->length -1 && num->digits[start] == '0') start++;
    if(start >0){
        for(int i=start;i<num->length;i++) num->digits[i - start] = num->digits[i];
        num->length -= start;
    }
    num->digits[num->length] = '\0';
}

// Add two BigNumbers: res = a + b
void addBigNumber(char *res, char *a, int len_a, char *b, int len_b) {
    int carry = 0;
    int i = len_a -1;
    int j = len_b -1;
    int k = (len_a > len_b) ? len_a : len_b;
    res[k] = '\0';
    k--;
    while(i >=0 || j >=0 || carry) {
        int digit_a = (i >=0) ? a[i]-'0' : 0;
        int digit_b = (j >=0) ? b[j]-'0' : 0;
        int sum = digit_a + digit_b + carry;
        carry = sum /10;
        res[k] = (sum %10) + '0';
        i--;
        j--;
        k--;
    }
    // Shift res if there are leading zeros
    int start = 0;
    while(start < (strlen(a) > strlen(b) ? strlen(a) : strlen(b)) && res[start] == '0') start++;
    if(start >0){
        memmove(res, res + start, strlen(res + start) +1);
    }
}

// Divide BigNumber by 2: res = a /2
void divideByTwo(char *res, char *a, int len_a) {
    int carry =0;
    for(int i=0;i<len_a;i++) {
        int current = carry *10 + (a[i] -'0');
        res[i] = (current /2) + '0';
        carry = current %2;
    }
    res[len_a] = '\0';
    // Remove leading zeros
    int start =0;
    while(start < len_a -1 && res[start] == '0') start++;
    if(start >0){
        memmove(res, res + start, len_a - start +1);
    }
}

// Compare two strings a and b, return 1 if a > b
int compare(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return -1;
    return strcmp(a, b);
}

int main(){
    int n;
    long long k;
    int p;
    scanf("%d %lld %d", &n, &k, &p);
    long long h[n];
    for(int i=0;i<n;i++) scanf("%lld", &h[i]);
    // Sort h[1..n-1] descendingly
    for(int i=1;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(h[j] > h[i]){
                long long tmp = h[i];
                h[i] = h[j];
                h[j] = tmp;
            }
        }
    }
    int two_p = 2*p;
    BigNumber t;
    initBigNumber(&t, h[0], two_p);
    int m = (k < n-1) ? k : (n-1);
    char a[MAX_DIGITS +1], b[MAX_DIGITS +1], sum[MAX_DIGITS +1];
    char divided[MAX_DIGITS +1];
    for(int i=0;i<m;i++){
        // a = t.digits
        strcpy(a, t.digits);
        int len_a = strlen(a);
        // b = h[i+1] *10^(2p)
        // Initialize b as h[i+1] and then append two_p zeros
        char temp_b[MAX_DIGITS +1];
        sprintf(temp_b, "%lld", h[i+1]);
        int len_temp = strlen(temp_b);
        strcpy(b, temp_b);
        for(int j=0;j<two_p;j++) b[len_temp +j] = '0';
        b[len_temp + two_p] = '\0';
        int len_b = strlen(b);
        // Add a and b, store in sum
        addBigNumber(sum, a, len_a, b, len_b);
        // Divide sum by 2, store in divided
        divideByTwo(divided, sum, strlen(sum));
        // Update t
        strcpy(t.digits, divided);
        t.length = strlen(t.digits);
    }
    // Prepare output
    // Convert t.digits to string with decimal point
    // Ensure at least two_p digits, pad with leading zeros if necessary
    int total_len = strlen(t.digits);
    if(total_len <= two_p){
        // Need to pad with leading zeros
        char temp_output[MAX_DIGITS +2];
        memset(temp_output, '0', two_p - total_len +1);
        temp_output[two_p - total_len] = '0';
        for(int i=two_p - total_len +1, j=0;i<two_p +1;i++, j++) temp_output[i] = t.digits[j];
        temp_output[two_p +1] = '\0';
        strcpy(t.digits, temp_output);
        total_len = strlen(t.digits);
    }
    // Insert decimal point
    char final_output[MAX_DIGITS +2];
    int int_part_len = total_len - two_p;
    if(int_part_len <=0){
        // "0." followed by zeros and digits
        strcpy(final_output, "0.");
        for(int i=0;i<two_p + int_part_len;i++) strcat(final_output, "0");
        strcat(final_output, t.digits);
    }
    else{
        strncpy(final_output, t.digits, int_part_len);
        final_output[int_part_len] = '.';
        final_output[int_part_len +1] = '\0';
        strcat(final_output, t.digits + int_part_len);
    }
    // Now, round or truncate to p decimal digits
    // We have two_p decimal digits, need to keep p, possibly round
    // As per problem, absolute error <1e- p is needed, so truncating is fine
    // But to keep at least p digits, take first p digits after decimal
    char integer_part[ MAX_DIGITS +1];
    char fraction_part[MAX_DIGITS +1];
    char *dot = strchr(final_output, '.');
    if(dot){
        int ip = dot - final_output;
        strncpy(integer_part, final_output, ip);
        integer_part[ip] = '\0';
        strcpy(fraction_part, dot +1);
    }
    else{
        strcpy(integer_part, final_output);
        fraction_part[0] = '\0';
    }
    // Ensure fraction_part has at least p digits
    int frac_len = strlen(fraction_part);
    while(frac_len < p){
        fraction_part[frac_len++] = '0';
        fraction_part[frac_len] = '\0';
    }
    // Take first p digits
    fraction_part[p] = '\0';
    // Remove trailing zeros if needed, but problem allows to keep at least p digits
    // So just print integer_part.fraction_part
    printf("%s.%s\n", integer_part, fraction_part);
}