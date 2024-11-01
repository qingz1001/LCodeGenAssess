#include <stdio.h>
#include <stdint.h>

int main(){
    int64_t N, M;
    scanf("%lld %lld", &N, &M);
    int64_t q = N / M;
    int64_t r = N % M;
    for(int64_t i=1;i<=M;i++){
        if(i <= M - r){
            printf("%lld", q);
        }
        else{
            printf("%lld", q+1);
        }
        if(i != M){
            putchar(' ');
        }
    }
    return 0;
}