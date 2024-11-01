#include <stdio.h>
#include <string.h>

#define MOD 19901013
#define MAXN 15

int n, m;
char grid[MAXN][MAXN];
int dp[MAXN][1 << MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            if (dp[i][j] == 0) continue;
            for (int k = 0; k < (1 << m); k++) {
                int valid = 1;
                for (int l = 0; l < m; l++) {
                    if ((k & (1 << l)) && (grid[i][l] == 'x' || (j & (1 << l)))) {
                        valid = 0;
                        break;
                    }
                }
                if (!valid) continue;
                int new_state = j | k;
                if (i == n - 1) {
                    dp[i + 1][new_state] = (dp[i + 1][new_state] + dp[i][j]) % MOD;
                } else {
                    int cross = 0;
                    for (int l = 0; l < m; l++) {
                        if ((k & (1 << l)) && (grid[i + 1][l] == '.')) {
                            cross = 1;
                            break;
                        }
                    }
                    if (cross) {
                        dp[i + 1][new_state] = (dp[i + 1][new_state] + dp[i][j]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < (1 << m); i++) {
        result = (result + dp[n][i]) % MOD;
    }
    printf("%d\n", result);

    return 0;
}