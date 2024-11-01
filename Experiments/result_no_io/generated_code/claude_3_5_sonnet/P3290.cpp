#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 100
#define MAX_M 12
#define MAX_C 6

long long dp[MAX_N + 1][1 << MAX_M][1 << MAX_M];
char template[2][MAX_C + 1];
int n, m, c, q;

int match(int mask1, int mask2) {
    for (int i = 0; i < c; i++) {
        int bit1 = (mask1 >> i) & 1;
        int bit2 = (mask2 >> i) & 1;
        if (template[0][i] == 'X' && template[1][i] == 'X') continue;
        if (template[0][i] != 'X' && template[1][i] == 'X') {
            if ((template[0][i] == 'W') != bit1) return 0;
        } else if (template[0][i] == 'X' && template[1][i] != 'X') {
            if ((template[1][i] == 'W') != bit2) return 0;
        } else {
            if ((template[0][i] == 'W') != bit1 || (template[1][i] == 'W') != bit2) return 0;
        }
    }
    return 1;
}

long long solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int mask1 = 0; mask1 < (1 << m); mask1++) {
            for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                if (dp[i][mask1][mask2] == 0) continue;
                for (int new_mask = 0; new_mask < (1 << m); new_mask++) {
                    int matched = 0;
                    if (i > 0) {
                        for (int j = 0; j <= m - c; j++) {
                            int submask1 = (mask2 >> j) & ((1 << c) - 1);
                            int submask2 = (new_mask >> j) & ((1 << c) - 1);
                            if (match(submask1, submask2)) {
                                matched = 1;
                                break;
                            }
                        }
                    }
                    if (matched || i == 0) {
                        dp[i + 1][mask2][new_mask] += dp[i][mask1][mask2];
                        dp[i + 1][mask2][new_mask] %= MOD;
                    }
                }
            }
        }
    }

    long long result = 0;
    for (int mask1 = 0; mask1 < (1 << m); mask1++) {
        for (int mask2 = 0; mask2 < (1 << m); mask2++) {
            result += dp[n][mask1][mask2];
            result %= MOD;
        }
    }
    return result;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &q);

    for (int i = 0; i < q; i++) {
        scanf("%s", template[0]);
        scanf("%s", template[1]);
        printf("%lld\n", solve());
    }

    return 0;
}