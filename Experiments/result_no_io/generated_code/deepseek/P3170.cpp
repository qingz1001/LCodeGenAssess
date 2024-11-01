#include <stdio.h>
#include <string.h>

#define MAXN 30
#define MAXM 30

int n, m;
char grid[MAXN][MAXM];
int dp[MAXN][MAXM][MAXN][MAXM][3];

int count_logos(int x1, int y1, int x2, int y2, int k) {
    if (k == 3) return 1;
    if (x1 >= n || y1 >= m || x2 >= n || y2 >= m) return 0;
    if (dp[x1][y1][x2][y2][k] != -1) return dp[x1][y1][x2][y2][k];

    int result = 0;

    // Try placing an L-shape starting at (x1, y1) and ending at (x2, y2)
    for (int i = x1; i < n; i++) {
        for (int j = y1; j < m; j++) {
            if (grid[i][j] == '#') continue;
            for (int p = x2; p < n; p++) {
                for (int q = y2; q < m; q++) {
                    if (grid[p][q] == '#') continue;
                    if (i == p && j == q) continue;
                    if (i <= p && j <= q) {
                        result += count_logos(i + 1, j + 1, p + 1, q + 1, k + 1);
                    }
                }
            }
        }
    }

    dp[x1][y1][x2][y2][k] = result;
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, -1, sizeof(dp));
    int result = count_logos(0, 0, 0, 0, 0);
    printf("%d\n", result);

    return 0;
}