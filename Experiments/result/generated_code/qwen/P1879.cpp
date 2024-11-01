#include <stdio.h>
#include <stdlib.h>

#define MOD 100000000

int dp[13][13][1<<12];

int solve(int m, int n, int mask, int last_col) {
    if (m == 0) return 1;
    if (dp[m][n][mask] != -1) return dp[m][n][mask];
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if ((mask & (1 << i)) == 0 && (last_col == -1 || !(last_col & (1 << i)))) {
            ans = (ans + solve(m-1, n, mask | (1 << i), i)) % MOD;
        }
    }
    
    dp[m][n][mask] = ans;
    return ans;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k < (1 << n); ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
    
    int grid[13][13];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    int total_ways = 0;
    for (int i = 0; i < (1 << n); ++i) {
        if (__builtin_popcount(i) > 0) {
            total_ways = (total_ways + solve(m, n, i, -1)) % MOD;
        } else {
            total_ways++;
        }
    }
    
    printf("%d\n", total_ways);
    return 0;
}