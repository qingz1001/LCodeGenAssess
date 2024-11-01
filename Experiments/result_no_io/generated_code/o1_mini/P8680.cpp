#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long sum = 0;
    for(int i = 1; i <= n; i++){
        int num = i;
        while(num > 0){
            int digit = num % 10;
            if(digit == 0 || digit == 1 || digit == 2 || digit == 9){
                sum += i;
                break;
            }
            num /= 10;
        }
    }
    printf("%lld\n", sum);
    return 0;
}