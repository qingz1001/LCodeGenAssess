#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to remove leading zeros
void remove_leading_zeros(char* num) {
    int len = strlen(num);
    int i = 0;
    while (i < len-1 && num[i] == '0') i++;
    if (i > 0) {
        memmove(num, num+i, len-i+1);
    }
}

// Function to compare two numeric strings
// Returns 1 if a > b, -1 if a < b, 0 if equal
int compare(const char* a, const char* b){
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return -1;
    for(int i=0;i<len_a;i++){
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
    }
    return 0;
}

// Function to multiply a numeric string by a number (unsigned long long)
// The result is stored in res, which should have enough space
void multiply(const char* num, unsigned long long x, char* res){
    int len = strlen(num);
    int carry = 0;
    res[len + 25] = '\0'; // Enough space
    int pos = len + 24;
    res[pos] = '\0';
    pos--;
    for(int i=len-1;i>=0;i--){
        unsigned long long temp = (num[i]-'0') * x + carry;
        res[pos--] = (temp % 10) + '0';
        carry = temp / 10;
    }
    while(carry > 0){
        res[pos--] = (carry % 10) + '0';
        carry /= 10;
    }
    // Shift to the beginning of res
    pos++;
    strcpy(res, res + pos);
    remove_leading_zeros(res);
}

// Function to subtract two numeric strings: a - b, assuming a >= b
void subtract(const char* a, const char* b, char* res){
    int len_a = strlen(a);
    int len_b = strlen(b);
    int carry = 0;
    res[len_a] = '\0';
    int pos = len_a -1;
    for(int i=1;i<=len_b;i++){
        int diff = (a[len_a -i] - '0') - (b[len_b -i] - '0') - carry;
        if(diff < 0){
            diff +=10;
            carry =1;
        }
        else{
            carry =0;
        }
        res[pos--] = diff + '0';
    }
    for(int i=len_a - len_b -1;i>=0;i--){
        if(carry ==0){
            res[i] = a[i] ;
        }
        else{
            int diff = (a[i] - '0') - carry;
            if(diff <0){
                res[i] = diff +10 + '0';
                carry =1;
            }
            else{
                res[i] = diff + '0';
                carry =0;
            }
        }
    }
    res[len_a] = '\0';
    remove_leading_zeros(res);
}

int main(){
    char N[2000001];
    char M[2000001];
    if(!fgets(N, sizeof(N), stdin)) return 0;
    if(!fgets(M, sizeof(M), stdin)) return 0;
    // Remove newline characters
    N[strcspn(N, "\n")] = 0;
    M[strcspn(M, "\n")] = 0;
    remove_leading_zeros(N);
    remove_leading_zeros(M);
    // Binary search for Q
    unsigned long long left =0, right = 6227020800ULL;
    unsigned long long ans =0;
    char temp[2000001];
    char product[2000001];
    while(left <= right){
        unsigned long long mid = left + (right - left)/2;
        multiply(M, mid, product);
        int cmp = compare(product, N);
        if(cmp <=0){
            ans = mid;
            left = mid +1;
        }
        else{
            right = mid -1;
        }
    }
    printf("%llu\n", ans);
    return 0;
}