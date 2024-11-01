#include <stdio.h>

int main(){
    long long N, M;
    scanf("%lld %lld", &N, &M);
    long long base = N / M;
    long long extra = N % M;
    for(long long i=0;i<M - extra;i++){
        printf("%lld ", base);
    }
    for(long long i=0;i<extra;i++){
        printf("%lld%c", base +1, (i == extra-1) ? '\n' : ' ');
    }
    if(extra ==0) printf("\n");
    return 0;
}