#include <stdio.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    if (N <= K) {
        printf("0\n");
        return 0;
    }

    long long need = 0;
    while (N > K) {
        long long half = (N + 1) / 2;
        need += half - K;
        N = half;
    }

    printf("%lld\n", need);
    return 0;
}