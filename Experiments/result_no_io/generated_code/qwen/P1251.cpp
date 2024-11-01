#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000
#define INF 1e9

typedef struct {
    int fast_clean_cost;
    int slow_clean_cost;
    int buy_new_cost;
} Cost;

int main() {
    int N, i;
    long long R[MAX_N];
    int p, m, f, n, s;
    Cost dp[MAX_N][MAX_N];

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%lld", &R[i]);
    }
    scanf("%d %d %d %d %d", &p, &m, &f, &n, &s);

    // Initialize the DP table
    for (i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j].fast_clean_cost = INF;
            dp[i][j].slow_clean_cost = INF;
            dp[i][j].buy_new_cost = INF;
        }
    }

    dp[0][0].fast_clean_cost = 0;
    dp[0][0].slow_clean_cost = 0;
    dp[0][0].buy_new_cost = 0;

    for (i = 1; i <= N; i++) {
        long long need = R[i - 1];
        for (int j = 0; j <= i; j++) {
            if (dp[j][i - j].fast_clean_cost != INF) {
                dp[j][i - j].fast_clean_cost += need * f;
                dp[j][i - j].slow_clean_cost += need * s;
                dp[j][i - j].buy_new_cost += need * p;
            }
            if (j > 0 && dp[j - 1][i - j].fast_clean_cost != INF) {
                dp[j][i - j].fast_clean_cost = fmin(dp[j][i - j].fast_clean_cost,
                                                   dp[j - 1][i - j].fast_clean_cost + need * f);
            }
            if (j > 0 && dp[j - 1][i - j].slow_clean_cost != INF) {
                dp[j][i - j].slow_clean_cost = fmin(dp[j][i - j].slow_clean_cost,
                                                   dp[j - 1][i - j].slow_clean_cost + need * s);
            }
            if (j > 0 && dp[j - 1][i - j].buy_new_cost != INF) {
                dp[j][i - j].buy_new_cost = fmin(dp[j][i - j].buy_new_cost,
                                                 dp[j - 1][i - j].buy_new_cost + need * p);
            }
        }
    }

    printf("%lld\n", fmin(fmin(dp[N][0].fast_clean_cost, dp[N][0].slow_clean_cost), dp[N][0].buy_new_cost));

    return 0;
}