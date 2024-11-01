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
    long long sum[MAX_N + 1] = {0};
    
    for (int i = N - 1; i >= 0; i--) {
        sum[i] = sum[i + 1] + Y[i];
    }

    for (int i = N - 1; i >= 0; i--) {
        dp[i] = C[i] * Y[i];
        long long stock = 0;
        for (int j = i + 1; j < N; j++) {
            stock += Y[j - 1];
            long long cost = C[i] * sum[i] + S * stock;
            if (cost < dp[i] + dp[j]) {
                dp[i] = cost;
            } else {
                break;
            }
        }
    }

    long long total_cost = 0;
    for (int i = 0; i < N; i++) {
        total_cost += dp[i];
    }

    printf("%lld\n", total_cost);

    return 0;
}