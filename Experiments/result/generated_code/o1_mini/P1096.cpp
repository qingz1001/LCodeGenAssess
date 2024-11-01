#include <stdio.h>

#define MAX_DIGITS 10000

int main(){
    int n;
    scanf("%d", &n);
    
    int digits[MAX_DIGITS];
    int len = 1;
    digits[0] = 2;
    
    for(int i = 1; i < n; i++){
        int carry = 0;
        for(int j = 0; j < len; j++){
            long long temp = (long long)digits[j] * 3 + carry;
            digits[j] = temp % 10;
            carry = temp / 10;
        }
        while(carry){
            digits[len++] = carry % 10;
            carry /= 10;
        }
    }
    
    for(int i = len-1; i >=0; i--){
        printf("%d", digits[i]);
    }
    
    return 0;
}