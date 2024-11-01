#include <stdio.h>

long long minNewBottles(long long N, int K) {
    long long newBottles = 0;
    long long totalBottles = N;
    
    while (totalBottles > K) {
        long long evenBottles = totalBottles - (totalBottles & 1);
        long long nextLevel = evenBottles / 2;
        
        if (nextLevel < K) {
            newBottles += K - nextLevel;
            totalBottles = K;
        } else {
            totalBottles = nextLevel + (totalBottles & 1);
        }
    }
    
    return newBottles;
}

int main() {
    long long N;
    int K;
    scanf("%lld %d", &N, &K);
    
    long long result = minNewBottles(N, K);
    printf("%lld\n", result);
    
    return 0;
}