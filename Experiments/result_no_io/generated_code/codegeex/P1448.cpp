#include <stdio.h>
#include <string.h>

int n, m;
int bad[110][220];
int dp[110][110][220];
int s[110][220];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        bad[x][y] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2 * i - 1; j++) {
            s[i][j] = s[i][j - 1] + (bad[i][j] == 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= 2 * i - 1; k++) {
                if (bad[i][k]) {
                    dp[i][j][k] = -1;
                } else {
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - 1][k - 1]);
                    if (k == 1 || k == 2 * i - 1) {
                        dp[i][j][k] += s[i][k];
                    } else {
                        dp[i][j][k] += max(s[i][k] - s[i][k - 1], s[i][k] - s[i][k - 2]);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2 * n - 1; j++) {
            ans = max(ans, dp[n][i][j]);
        }
    }

    printf("%d\n", ans);
    return 0;
}