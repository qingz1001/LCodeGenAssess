#include <stdio.h>
#include <string.h>

#define MAX_N 9
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int N;
int grid[MAX_N + 1][MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1][MAX_N + 1][MAX_N + 1];

int main() {
    scanf("%d", &N);
    
    memset(grid, 0, sizeof(grid));
    memset(dp, 0, sizeof(dp));
    
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
                    int temp = dp[i-1][j][k-1][l];
                    temp = MAX(temp, dp[i-1][j][k][l-1]);
                    temp = MAX(temp, dp[i][j-1][k-1][l]);
                    temp = MAX(temp, dp[i][j-1][k][l-1]);
                    
                    dp[i][j][k][l] = temp;
                    
                    if (i == k && j == l) {
                        dp[i][j][k][l] += grid[i][j];
                    } else {
                        dp[i][j][k][l] += grid[i][j] + grid[k][l];
                    }
                }
            }
        }
    }
    
    printf("%d\n", dp[N][N][N][N]);
    
    return 0;
}