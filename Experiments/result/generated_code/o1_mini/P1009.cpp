#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

int main(){
    int n;
    scanf("%d", &n);
    
    // Initialize factorial as 1
    int factorial[MAX_DIGITS];
    memset(factorial, 0, sizeof(factorial));
    factorial[0] = 1;
    int fact_len = 1;
    
    // Initialize sum as 0
    int sum[MAX_DIGITS];
    memset(sum, 0, sizeof(sum));
    int sum_len = 0;
    
    for(int i=1;i<=n;i++){
        if(i > 1){
            // Multiply factorial by i
            int carry = 0;
            for(int j=0; j < fact_len; j++){
                long temp = (long)factorial[j] * i + carry;
                factorial[j] = temp % 10;
                carry = temp / 10;
            }
            while(carry > 0){
                factorial[fact_len++] = carry % 10;
                carry /= 10;
            }
        }
        // Add factorial to sum
        if(sum_len == 0){
            memcpy(sum, factorial, fact_len * sizeof(int));
            sum_len = fact_len;
        }
        else{
            int carry = 0;
            int max_len = (sum_len > fact_len) ? sum_len : fact_len;
            for(int j=0; j < max_len; j++){
                if(j < fact_len){
                    sum[j] += factorial[j] + carry;
                }
                else{
                    sum[j] += carry;
                }
                if(sum[j] >= 10){
                    sum[j] -= 10;
                    carry = 1;
                }
                else{
                    carry = 0;
                }
            }
            if(carry){
                sum[max_len++] = carry;
                sum_len = max_len;
            }
            else{
                sum_len = (sum_len > fact_len) ? sum_len : fact_len;
            }
        }
    }
    
    // Print sum
    for(int i = sum_len-1; i >=0; i--){
        printf("%d", sum[i]);
    }
    return 0;
}