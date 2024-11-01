#include <stdio.h>
#include <math.h>

int main() {
    long long N, K;
    scanf("%lld %lld", &N, &K);

    int count = 0;
    while (N > K) {
        long long sum = 1;
        while (sum * 2 <= N) {
            sum *= 2;
        }
        N -= sum;
        count++;
    }

    if (N < K) {
        count += K - N;
    }

    printf("%d\n", count);
    return 0;
}