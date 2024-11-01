#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int ans = 0;
    for (int len = 1; len <= n && len <= m; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            for (int j = 1; j + len - 1 <= m; j++) {
                if (len == 1) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = (matrix[i][j] == matrix[i][j + len - 1] &&
                                matrix[i][j] == matrix[i + len - 1][j] &&
                                matrix[i][j] == matrix[i + len - 1][j + len - 1]) ? 1 : 0;
                    if (dp[i][j] && len > 2) {
                        dp[i][j] &= dp[i + 1][j + 1];
                    }
                }
                if (dp[i][j]) {
                    ans++;
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}