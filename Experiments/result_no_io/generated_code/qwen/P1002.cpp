#include <stdio.h>

#define MAXN 25

int n, m, xk, yk;
int dp[MAXN][MAXN];

void init() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }
}

int is_valid(int x, int y) {
    return x >= 0 && x <= n && y >= 0 && y <= m;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &xk, &yk);
    init();

    dp[0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (!is_valid(i, j)) continue;
            if (i == xk && j == yk) continue;

            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
        }
    }

    printf("%d\n", dp[n][m]);

    return 0;
}