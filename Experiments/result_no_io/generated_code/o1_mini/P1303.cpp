#include <stdio.h>
#include <string.h>

#define MAX 4001

int main(){
    char num1[2001], num2[2001];
    scanf("%s", num1);
    scanf("%s", num2);
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    
    // Reverse num1
    for(int i=0; i<len1/2; i++){
        char temp = num1[i];
        num1[i] = num1[len1-1-i];
        num1[len1-1-i] = temp;
    }
    
    // Reverse num2
    for(int i=0; i<len2/2; i++){
        char temp = num2[i];
        num2[i] = num2[len2-1-i];
        num2[len2-1-i] = temp;
    }
    
    int result[MAX] = {0};
    
    // Multiply each digit
    for(int i=0; i<len1; i++){
        int digit1 = num1[i] - '0';
        for(int j=0; j<len2; j++){
            int digit2 = num2[j] - '0';
            result[i+j] += digit1 * digit2;
        }
    }
    
    // Handle carry
    for(int i=0; i<len1 + len2; i++){
        if(result[i] >= 10){
            result[i+1] += result[i] / 10;
            result[i] %= 10;
        }
    }
    
    // Find the highest non-zero digit
    int result_len = len1 + len2;
    while(result_len > 1 && result[result_len-1] == 0){
        result_len--;
    }
    
    // Print the result in reverse
    for(int i=result_len-1; i>=0; i--){
        printf("%d", result[i]);
    }
    printf("\n");
    
    return 0;
}