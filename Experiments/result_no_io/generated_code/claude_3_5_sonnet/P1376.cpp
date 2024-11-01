#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);

    int C[MAX_N], Y[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &C[i], &Y[i]);
    }

    long long dp[MAX_N] = {0};
    long long sum = 0;
    long long result = 0;

    for (int i = 0; i < N; i++) {
        sum += Y[i];
        dp[i] = C[i] * sum;
        
        for (int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + C[i] * (sum - (i - j) * Y[j]) + S * (i - j) * Y[j]);
        }

        result = dp[i];
    }

    printf("%lld\n", result);

    return 0;
}