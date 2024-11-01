#include <stdio.h>

#define MAXN 1010

int n, m;
int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int ans = 0;
    for (int size = 1; size <= n && size <= m; ++size) {
        for (int i = 1; i + size - 1 <= n; ++i) {
            for (int j = 1; j + size - 1 <= m; ++j) {
                if (size == 1) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = (matrix[i][j] == matrix[i][j + size - 1] &&
                                matrix[i][j] == matrix[i + size - 1][j] &&
                                matrix[i][j] == matrix[i + size - 1][j + size - 1]) ? dp[i + 1][j + 1] + 1 : 0;
                }
                ans += dp[i][j];
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}