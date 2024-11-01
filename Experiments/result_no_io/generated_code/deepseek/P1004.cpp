#include <stdio.h>
#include <string.h>

#define MAXN 10
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int grid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int main() {
    int N;
    scanf("%d", &N);
    
    memset(grid, 0, sizeof(grid));
    memset(dp, 0, sizeof(dp));
    
    int x, y, v;
    while (1) {
        scanf("%d %d %d", &x, &y, &v);
        if (x == 0 && y == 0 && v == 0) break;
        grid[x][y] = v;
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                for (int l = 1; l <= N; l++) {
                    int val = grid[i][j] + grid[k][l];
                    if (i == k && j == l) val -= grid[i][j];
                    
                    dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i-1][j][k-1][l] + val);
                    dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i-1][j][k][l-1] + val);
                    dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i][j-1][k-1][l] + val);
                    dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i][j-1][k][l-1] + val);
                }
            }
        }
    }
    
    printf("%d\n", dp[N][N][N][N]);
    
    return 0;
}