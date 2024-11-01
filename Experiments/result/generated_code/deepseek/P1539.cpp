#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 15

int n, m;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN][1 << MAXN];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int is_valid(int x, int y, int mask) {
    if (grid[x][y] == '0' && (mask & (1 << y))) return 0;
    if (grid[x][y] == '1' && !(mask & (1 << y))) return 0;
    if (y > 0 && (mask & (1 << (y - 1))) && (mask & (1 << y))) return 0;
    return 1;
}

int solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (dp[i][j][mask] == 0) continue;

                int new_mask1 = mask;
                int new_mask2 = mask | (1 << j);

                if (j < m - 1) {
                    if (is_valid(i, j, new_mask1)) {
                        dp[i][j + 1][new_mask1] = (dp[i][j + 1][new_mask1] + dp[i][j][mask]) % MOD;
                    }
                    if (is_valid(i, j, new_mask2)) {
                        dp[i][j + 1][new_mask2] = (dp[i][j + 1][new_mask2] + dp[i][j][mask]) % MOD;
                    }
                } else {
                    if (is_valid(i, j, new_mask1)) {
                        dp[i + 1][0][new_mask1 >> 1] = (dp[i + 1][0][new_mask1 >> 1] + dp[i][j][mask]) % MOD;
                    }
                    if (is_valid(i, j, new_mask2)) {
                        dp[i + 1][0][new_mask2 >> 1] = (dp[i + 1][0][new_mask2 >> 1] + dp[i][j][mask]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        result = (result + dp[n][0][mask]) % MOD;
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    printf("%d\n", solve());
    return 0;
}