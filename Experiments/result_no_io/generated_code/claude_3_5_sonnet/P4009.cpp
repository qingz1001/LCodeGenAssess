#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 10

int n, k, a, b, c;
int grid[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_K+1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d %d %d", &n, &k, &a, &b, &c);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][k] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int fuel = 1; fuel <= k; fuel++) {
                if (i > 0) {
                    dp[i][j][fuel] = min(dp[i][j][fuel], dp[i-1][j][fuel+1] + b);
                }
                if (j > 0) {
                    dp[i][j][fuel] = min(dp[i][j][fuel], dp[i][j-1][fuel+1]);
                }
                if (grid[i][j] || (i == 0 && j == 0)) {
                    for (int prevFuel = 1; prevFuel <= k; prevFuel++) {
                        dp[i][j][k] = min(dp[i][j][k], dp[i][j][prevFuel] + a);
                    }
                }
                if (i < n-1) {
                    dp[i+1][j][fuel-1] = min(dp[i+1][j][fuel-1], dp[i][j][fuel]);
                }
                if (j < n-1) {
                    dp[i][j+1][fuel-1] = min(dp[i][j+1][fuel-1], dp[i][j][fuel]);
                }
            }
        }
    }
    
    int minCost = INT_MAX;
    for (int fuel = 0; fuel <= k; fuel++) {
        minCost = min(minCost, dp[n-1][n-1][fuel]);
    }
    
    int additionalStations = 0;
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (!grid[i][j]) {
                int costWithStation = minCost;
                for (int fuel = 0; fuel <= k; fuel++) {
                    costWithStation = min(costWithStation, dp[i][j][fuel] + a + c);
                }
                if (costWithStation < minCost) {
                    minCost = costWithStation;
                    additionalStations++;
                }
            }
        }
    }
    
    printf("%d\n", minCost);
    
    return 0;
}