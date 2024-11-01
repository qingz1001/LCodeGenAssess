#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to remove leading zeros
void trim_leading(char *s) {
    int len = strlen(s);
    int i = 0;
    while (i < len-1 && s[i] == '0') i++;
    if (i > 0) {
        memmove(s, s+i, len-i+1);
    }
}

// Compare two numeric strings
// Returns 1 if a > b, -1 if a < b, 0 if equal
int compare(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;
    for(int i=0;i<len_a;i++) {
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
    }
    return 0;
}

// Subtract b from a. Assume a >= b
void subtract(char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int carry = 0;
    for(int i=1;i<=len_a;i++) {
        int digit_a = a[len_a - i] - '0';
        int digit_b = (i <= len_b) ? (b[len_b - i] - '0') : 0;
        int diff = digit_a - digit_b - carry;
        if(diff < 0) {
            diff += 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        a[len_a - i] = diff + '0';
    }
    a[len_a] = '\0';
    trim_leading(a);
}

// Multiply a numeric string by a single digit (0-9)
void multiply_digit(const char *a, int digit, char *res) {
    if(digit == 0) {
        res[0] = '0';
        res[1] = '\0';
        return;
    }
    int carry = 0;
    int len_a = strlen(a);
    char temp[22000];
    int idx = 0;
    for(int i=len_a-1;i>=0;i--){
        int prod = (a[i]-'0') * digit + carry;
        temp[idx++] = (prod % 10) + '0';
        carry = prod / 10;
    }
    if(carry) temp[idx++] = carry + '0';
    // Reverse the result
    for(int i=0;i<idx;i++) res[i] = temp[idx-1-i];
    res[idx] = '\0';
}

// Main division function: dividend / divisor
long long divide(const char *dividend, const char *divisor) {
    int len = strlen(dividend);
    char current[22000] = "0";
    char quotient[22000] = "";
    for(int i=0;i<len;i++) {
        // Append next digit to current
        int curr_len = strlen(current);
        char temp[22000];
        strcpy(temp, current);
        temp[curr_len] = dividend[i];
        temp[curr_len+1] = '\0';
        trim_leading(temp);
        strcpy(current, temp);
        
        // Find the quotient digit
        int q = 0;
        while(compare(current, divisor) >= 0 && q < 10) q++;
        q--;
        // If q < 0, set to 0
        if(q < 0) q = 0;
        
        // Append q to quotient
        char q_char[2];
        q_char[0] = q + '0';
        q_char[1] = '\0';
        strcat(quotient, q_char);
        
        if(q > 0){
            // current = current - divisor * q
            char mul[22000];
            multiply_digit(divisor, q, mul);
            subtract(current, mul);
        }
    }
    trim_leading(quotient);
    if(strcmp(quotient, "") == 0) return 0;
    // Convert quotient to long long
    return atoll(quotient);
}

int main(){
    char N[22000], M[22000];
    // Read N
    scanf("%s", N);
    // Read M
    scanf("%s", M);
    // Edge case: M == "0" is not possible since M is positive
    // Compute N / M
    long long result = divide(N, M);
    printf("%lld\n", result);
    return 0;
}