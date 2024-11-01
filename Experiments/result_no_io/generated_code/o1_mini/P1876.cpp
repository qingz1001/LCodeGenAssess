#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

int main(){
    ull N;
    scanf("%llu", &N);
    ull K = (ull)sqrt((double)N);
    while((K+1)*(K+1) <= N) K++;
    while(K*K > N) K--;
    for(ull i=1;i<=K;i++) printf("%llu ", i*i);
    return 0;
}