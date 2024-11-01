#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int n, m;
int bad[MAXN * MAXN];
int dp[MAXN + 1][MAXN + 1];

int is_good(int x, int y) {
    if (x <= 0 || x > n || y <= 0 || y > 2 * n - 1) return 0;
    if (bad[(x - 1) * 2 * n + y]) return 0;
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        bad[(x - 1) * 2 * n + y] = 1;
    }

    dp[0][0] = 1;
    for (int size = 1; size <= n; size++) {
        for (int row = 1; row <= n; row++) {
            for (int col = 1; col <= 2 * n - row; col++) {
                if (!is_good(row, col)) continue;
                if (col + 2 * size <= 2 * n - row && is_good(row, col + 2 * size)) {
                    dp[row][col] += dp[row][col + 2 * size];
                }
                if (row + size <= n && is_good(row + size, col)) {
                    dp[row][col] += dp[row + size][col];
                }
                if (col + 2 * size <= 2 * n - row && row + size <= n && is_good(row + size, col + 2 * size)) {
                    dp[row][col] -= dp[row][col + 2 * size] * dp[row + size][col + 2 * size];
                }
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2 * n - i; j++) {
            if (dp[i][j] > 0) {
                result = i * i + j * j / 4;
                break;
            }
        }
        if (result > 0) break;
    }

    printf("%d\n", result);

    return 0;
}