#include <stdio.h>

int main(){
    unsigned int N, K;
    scanf("%u %u", &N, &K);
    unsigned long long x = 0;
    unsigned long long current = N;
    while(__builtin_popcount(current) > K){
        unsigned long long add = current & (-current);
        x += add;
        current += add;
    }
    printf("%llu\n", x);
    return 0;
}