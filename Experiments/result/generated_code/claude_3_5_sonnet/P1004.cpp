#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define max(a, b) ((a) > (b) ? (a) : (b))

int N;
int grid[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_N][MAX_N];

int main() {
    memset(grid, 0, sizeof(grid));
    memset(dp, 0, sizeof(dp));

    scanf("%d", &N);

    int x, y, val;
    while (1) {
        scanf("%d %d %d", &x, &y, &val);
        if (x == 0 && y == 0 && val == 0) break;
        grid[x][y] = val;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                for (int l = 1; l <= N; l++) {
                    int value = grid[i][j];
                    if (i != k) value += grid[k][l];

                    dp[i][j][k][l] = max(max(dp[i-1][j][k-1][l], dp[i-1][j][k][l-1]),
                                         max(dp[i][j-1][k-1][l], dp[i][j-1][k][l-1])) + value;
                }
            }
        }
    }

    printf("%d\n", dp[N][N][N][N]);

    return 0;
}