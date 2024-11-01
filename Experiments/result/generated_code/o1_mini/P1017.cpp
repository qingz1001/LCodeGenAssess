#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, R;
    scanf("%d %d", &n, &R);
    int base = abs(R);
    
    if(n == 0){
        printf("%d=0(base-%d)\n", n, base);
        return 0;
    }
    
    char digits[100];
    int len = 0;
    int temp_n = n;
    
    while(temp_n != 0){
        int remainder = temp_n % R;
        int quotient = temp_n / R;
        
        if(remainder < 0){
            remainder += base;
            quotient += 1;
        }
        
        temp_n = quotient;
        
        if(remainder < 10){
            digits[len++] = '0' + remainder;
        }
        else{
            digits[len++] = 'A' + (remainder - 10);
        }
    }
    
    // Reverse the digits
    char result[100];
    for(int i = 0; i < len; i++){
        result[i] = digits[len - 1 - i];
    }
    result[len] = '\0';
    
    printf("%d=%s(base-%d)\n", n, result, base);
    return 0;
}