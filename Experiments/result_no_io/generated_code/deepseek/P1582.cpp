#include <stdio.h>
#include <math.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    int count = 0;
    while ((N & (N - 1)) != 0 || __builtin_popcountll(N) > K) {
        N++;
        count++;
    }

    printf("%d\n", count);
    return 0;
}