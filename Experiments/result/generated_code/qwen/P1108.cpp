#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define INF 1 << 30

int main() {
    int N;
    scanf("%d", &N);
    int prices[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &prices[i]);
    }

    int max_buy_times = 0;
    int max_schemes = 0;

    // Dynamic programming to find the maximum buy times
    int dp[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dp[i][j] = -INF;
        }
    }

    for (int i = 0; i < N; ++i) {
        dp[i][i] = 0;
    }

    for (int length = 2; length <= N; ++length) {
        for (int i = 0; i + length - 1 < N; ++i) {
            int j = i + length - 1;
            for (int k = i; k < j; ++k) {
                if (prices[k] > prices[j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + 1;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        if (dp[0][i] > max_buy_times) {
            max_buy_times = dp[0][i];
            max_schemes = 1;
        } else if (dp[0][i] == max_buy_times) {
            max_schemes++;
        }
    }

    printf("%d %d\n", max_buy_times, max_schemes);

    return 0;
}