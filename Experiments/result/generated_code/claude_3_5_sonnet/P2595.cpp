#include <stdio.h>
#include <string.h>

#define MAX_N 15
#define MAX_M 15
#define MOD 19901013

char grid[MAX_N][MAX_M];
int n, m;
int dp[1 << MAX_M][1 << MAX_M];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int solve() {
    int full_mask = (1 << m) - 1;
    dp[0][full_mask] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            if (dp[i][j] == 0) continue;

            for (int k = 0; k < (1 << m); k++) {
                int valid = 1;
                for (int l = 0; l < m; l++) {
                    if (grid[i][l] == 'x' && (k & (1 << l))) {
                        valid = 0;
                        break;
                    }
                    if (l < m - 1 && (k & (3 << l)) == 0 && (j & (1 << l)) == 0 && (j & (1 << (l + 1))) == 0) {
                        valid = 0;
                        break;
                    }
                }
                if (!valid) continue;

                int next_j = 0;
                for (int l = 0; l < m; l++) {
                    if ((k & (1 << l)) || (j & (1 << l))) {
                        next_j |= (1 << l);
                    }
                }

                dp[i + 1][next_j] = (dp[i + 1][next_j] + dp[i][j]) % MOD;
            }
        }
    }

    int result = 0;
    for (int j = 0; j < (1 << m); j++) {
        if (count_bits(j) == m) {
            result = (result + dp[n][j]) % MOD;
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}