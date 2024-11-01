#include <stdio.h>
#include <string.h>

#define MAX_N 9
#define INF 0x3f3f3f3f

int n;
int grid[MAX_N][MAX_N];
int dp[1<<MAX_N][MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(dp, -INF, sizeof(dp));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dp[1<<i][i][j] = grid[i][j];
        }
    }

    int result = -INF;
    for(int mask = 1; mask < (1<<n); mask++) {
        for(int i = 0; i < n; i++) {
            if(!(mask & (1<<i))) continue;
            for(int j = 0; j < n; j++) {
                if(dp[mask][i][j] == -INF) continue;
                result = max(result, dp[mask][i][j]);
                
                if(i > 0 && !(mask & (1<<(i-1)))) {
                    int new_mask = mask | (1<<(i-1));
                    dp[new_mask][i-1][j] = max(dp[new_mask][i-1][j], dp[mask][i][j] + grid[i-1][j]);
                }
                if(i < n-1 && !(mask & (1<<(i+1)))) {
                    int new_mask = mask | (1<<(i+1));
                    dp[new_mask][i+1][j] = max(dp[new_mask][i+1][j], dp[mask][i][j] + grid[i+1][j]);
                }
                if(j > 0 && !(mask & (1<<(j-1)))) {
                    int new_mask = mask | (1<<(j-1));
                    dp[new_mask][i][j-1] = max(dp[new_mask][i][j-1], dp[mask][i][j] + grid[i][j-1]);
                }
                if(j < n-1 && !(mask & (1<<(j+1)))) {
                    int new_mask = mask | (1<<(j+1));
                    dp[new_mask][i][j+1] = max(dp[new_mask][i][j+1], dp[mask][i][j] + grid[i][j+1]);
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}