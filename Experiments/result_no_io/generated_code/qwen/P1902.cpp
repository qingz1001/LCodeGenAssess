#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 2000000

int n, m;
int p[MAXN][MAXN];
int dp[MAXN][MAXN];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = INF;
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &p[i][j]);
        }
    }

    init();
    dp[1][1] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            dp[i][j] = min(dp[i][j], dp[i-1][j] + max(p[i][j], dp[i-1][j]));
            dp[i][j] = min(dp[i][j], dp[i][j-1] + max(p[i][j], dp[i][j-1]));
        }
    }

    printf("%d\n", dp[n][m]);

    return 0;
}