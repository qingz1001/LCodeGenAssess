#include <stdio.h>
#include <string.h>

#define MAX 1000

int main(){
    int n;
    scanf("%d", &n);
    int digits[MAX];
    memset(digits, 0, sizeof(digits));
    digits[0] = 1;
    int len = 1;
    // Multiply by 2, n+1 times
    for(int i=0;i<=n;i++){
        int carry =0;
        for(int j=0;j<len;j++){
            int temp = digits[j]*2 + carry;
            digits[j] = temp %10;
            carry = temp /10;
        }
        if(carry) {
            digits[len++] = carry;
        }
    }
    // Subtract 2
    digits[0] -=2;
    int borrow =0;
    if(digits[0] <0){
        digits[0] +=10;
        borrow =1;
    }
    else{
        borrow =0;
    }
    int j =1;
    while(borrow && j < len){
        digits[j] -=1;
        if(digits[j] <0){
            digits[j] +=10;
            borrow =1;
            j++;
        }
        else{
            borrow =0;
        }
    }
    // Adjust length if highest digit is 0
    if(digits[len-1]==0 && len >1){
        len--;
    }
    // Print digits in reverse
    for(int i=len-1;i>=0;i--){
        printf("%d", digits[i]);
    }
    printf("\n");
    return 0;
}