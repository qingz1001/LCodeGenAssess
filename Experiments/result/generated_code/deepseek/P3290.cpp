#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 100
#define MAXM 12
#define MAXC 6
#define MAXQ 5

int n, m, c, q;
char templates[MAXQ][2][MAXC + 1];
int dp[MAXN + 1][1 << MAXM][1 << MAXM];

int count_valid_boards(int template_index) {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int mask1 = 0; mask1 < (1 << m); mask1++) {
            for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                if (dp[i][mask1][mask2] == 0) continue;

                for (int new_mask = 0; new_mask < (1 << m); new_mask++) {
                    int valid = 1;
                    for (int j = 0; j < m - c + 1; j++) {
                        int match1 = 1, match2 = 1;
                        for (int k = 0; k < c; k++) {
                            if ((mask1 & (1 << (j + k))) != (templates[template_index][0][k] == 'B' ? 1 << (j + k) : 0)) match1 = 0;
                            if ((mask2 & (1 << (j + k))) != (templates[template_index][1][k] == 'B' ? 1 << (j + k) : 0)) match2 = 0;
                        }
                        if (match1 && match2) {
                            valid = 0;
                            break;
                        }
                    }
                    if (valid) {
                        dp[i + 1][mask2][new_mask] = (dp[i + 1][mask2][new_mask] + dp[i][mask1][mask2]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int mask1 = 0; mask1 < (1 << m); mask1++) {
        for (int mask2 = 0; mask2 < (1 << m); mask2++) {
            result = (result + dp[n][mask1][mask2]) % MOD;
        }
    }
    return result;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &q);
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%s", templates[i][j]);
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", count_valid_boards(i));
    }

    return 0;
}