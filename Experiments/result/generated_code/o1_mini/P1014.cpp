#include <stdio.h>

int main(){
    long long N;
    scanf("%lld", &N);
    long long s=2;
    while((s*(s-1))/2 < N) s++;
    long long prior = (s-1)*(s-2)/2;
    long long k = N - prior;
    long long num, den;
    if(s % 2 == 0){
        num = s - k;
        den = k;
    }
    else{
        num = k;
        den = s - k;
    }
    printf("%lld/%lld", num, den);
    return 0;
}