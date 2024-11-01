#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN];
int dp[MAXN][2];
int cost[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

void preprocess() {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int mid = (i + j) / 2;
            for (int k = i; k <= j; k++) {
                cost[i][j] += abs(a[k] - a[mid]);
            }
        }
    }
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < j; k++) {
                dp[j][i % 2] = min(dp[j][i % 2], dp[k][(i - 1) % 2] + cost[k + 1][j]);
            }
        }
    }

    return dp[n][m % 2];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    preprocess();
    int result = solve();
    printf("%d\n", result);

    return 0;
}