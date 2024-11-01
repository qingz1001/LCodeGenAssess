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

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (dp[i][j][mask] == 0) continue;

                int ni = i, nj = j + 1;
                if (nj == m) {
                    ni++;
                    nj = 0;
                }

                if (grid[i][j] == '0') {
                    dp[ni][nj][mask & ~(1 << j)] = (dp[ni][nj][mask & ~(1 << j)] + dp[i][j][mask]) % MOD;
                } else if (grid[i][j] == '1') {
                    if ((j == 0 || !(mask & (1 << (j - 1)))) && !(mask & (1 << j))) {
                        dp[ni][nj][mask | (1 << j)] = (dp[ni][nj][mask | (1 << j)] + dp[i][j][mask]) % MOD;
                    }
                } else {
                    dp[ni][nj][mask & ~(1 << j)] = (dp[ni][nj][mask & ~(1 << j)] + dp[i][j][mask]) % MOD;
                    if ((j == 0 || !(mask & (1 << (j - 1)))) && !(mask & (1 << j))) {
                        dp[ni][nj][mask | (1 << j)] = (dp[ni][nj][mask | (1 << j)] + dp[i][j][mask]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        result = (result + dp[n][0][mask]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}