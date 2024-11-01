#include <stdio.h>
#define MOD 1000000007
#define MAX_R 100
#define MAX_C 100

int R, C, K;
int grid[MAX_R][MAX_C];
long long dp[MAX_R][MAX_C];

long long solve() {
    dp[0][0] = 1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (int x = 0; x < i; x++) {
                for (int y = 0; y < j; y++) {
                    if (grid[x][y] != grid[i][j]) {
                        dp[i][j] = (dp[i][j] + dp[x][y]) % MOD;
                    }
                }
            }
        }
    }
    return dp[R-1][C-1];
}

int main() {
    scanf("%d %d %d", &R, &C, &K);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    printf("%lld\n", solve());
    return 0;
}