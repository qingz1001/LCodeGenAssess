#include <stdio.h>
#include <string.h>

#define MAX 210

int main(){
    int n;
    scanf("%d", &n);
    // Initialize result as "1"
    char result[MAX];
    result[0] = '1';
    result[1] = '\0';
    int len = 1;
    
    // Function to multiply result by (n-i+1)
    for(int i=1;i<=n;i++){
        int carry = 0;
        for(int j=0;j<len;j++){
            int temp = (result[j]-'0') * i + carry;
            result[j] = (temp % 10) + '0';
            carry = temp /10;
        }
        while(carry){
            result[len++] = (carry %10) + '0';
            carry /=10;
        }
        result[len] = '\0';
    }
    
    // Print the result in reverse
    for(int i=len-1;i>=0;i--){
        printf("%c", result[i]);
    }
    printf("\n");
    return 0;
}