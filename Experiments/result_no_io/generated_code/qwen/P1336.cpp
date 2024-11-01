#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 20
#define INF 1e9

int n, m;
long long dp[MAX_N + 1][MAX_M];

long long cost(int i, int x) {
    return (long long)i * pow(x, i);
}

void solve() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k <= i; ++k) {
                dp[i][j] = fmin(dp[i][j], dp[i - k][j - 1] + cost(j + 1, k));
            }
        }
    }

    printf("%lld\n", dp[n][m - 1]);
}

int main() {
    scanf("%d %d", &n, &m);
    solve();
    return 0;
}