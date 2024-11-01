#include <stdio.h>
#include <string.h>

#define N 9
#define OFFSET 1000000

int n;
int grid[N][N];
int dp[1 << N][N][N];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(dp, 0, sizeof(dp));

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mask & (1 << i)) {
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && !(mask & (1 << ni))) {
                            dp[mask | (1 << ni)][ni][nj] = max(dp[mask | (1 << ni)][ni][nj], dp[mask][i][j] + grid[ni][nj]);
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result = max(result, dp[mask][i][j]);
            }
        }
    }

    printf("%d\n", result);
    return 0;
}