#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

int main(){
    int n;
    scanf("%d", &n);
    if(n ==1){
        printf("0\n");
        return 0;
    }
    int digits[MAX_DIGITS];
    memset(digits, 0, sizeof(digits));
    digits[0] =1;
    int size=1;
    // Multiply by 2, n times
    for(int i=0;i<n;i++){
        int carry=0;
        for(int j=0;j<size;j++){
            int temp = digits[j]*2 + carry;
            digits[j] = temp %10;
            carry = temp /10;
        }
        while(carry){
            digits[size++] = carry%10;
            carry /=10;
        }
    }
    // Multiply by (n-1)
    int multiplier = n-1;
    if(multiplier !=0){
        int carry=0;
        for(int j=0;j<size;j++){
            int temp = digits[j]*multiplier + carry;
            digits[j] = temp %10;
            carry = temp /10;
        }
        while(carry){
            digits[size++] = carry%10;
            carry /=10;
        }
    }
    // Handle n=1 separately
    if(n==1){
        printf("0\n");
        return 0;
    }
    // Print in reverse
    for(int j=size-1; j>=0; j--){
        printf("%d", digits[j]);
    }
    printf("\n");
    return 0;
}