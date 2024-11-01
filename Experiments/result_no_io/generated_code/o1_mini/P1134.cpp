#include <stdio.h>
#include <stdint.h>

int main(){
    int N;
    scanf("%d", &N);
    uint64_t res = 1;
    for(int i=2;i<=N;i++){
        res *= i;
        while(res%10 ==0){
            res /=10;
        }
        res %= 100000000;
    }
    printf("%llu\n", res%10);
    return 0;
}