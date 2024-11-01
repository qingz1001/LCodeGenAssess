#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 100
#define MAX_M 12
#define MAX_C 6

long long dp[2][1 << MAX_M][1 << MAX_M];
char template[2][MAX_C + 1];
int n, m, c, q;

int main() {
    scanf("%d %d %d %d", &n, &m, &c, &q);

    while (q--) {
        scanf("%s %s", template[0], template[1]);

        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int curr = i % 2;
                int next = 1 - curr;
                memset(dp[next], 0, sizeof(dp[next]));

                for (int mask1 = 0; mask1 < (1 << m); mask1++) {
                    for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                        if (dp[curr][mask1][mask2] == 0) continue;

                        for (int state = 0; state < 3; state++) {
                            int newMask1 = ((mask1 << 1) | (state & 1)) & ((1 << m) - 1);
                            int newMask2 = ((mask2 << 1) | (state >> 1)) & ((1 << m) - 1);

                            if (i >= 1 && j >= c - 1) {
                                int valid = 1;
                                for (int k = 0; k < c; k++) {
                                    int bit1 = (newMask1 >> (m - c + k)) & 1;
                                    int bit2 = (newMask2 >> (m - c + k)) & 1;
                                    if ((template[0][k] == 'W' && bit1 == 0) || (template[0][k] == 'B' && bit1 == 1) ||
                                        (template[1][k] == 'W' && bit2 == 0) || (template[1][k] == 'B' && bit2 == 1)) {
                                        valid = 0;
                                        break;
                                    }
                                }
                                if (!valid) continue;
                            }

                            dp[next][newMask1][newMask2] = (dp[next][newMask1][newMask2] + dp[curr][mask1][mask2]) % MOD;
                        }
                    }
                }
            }
        }

        long long result = 0;
        for (int mask1 = 0; mask1 < (1 << m); mask1++) {
            for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                result = (result + dp[n % 2][mask1][mask2]) % MOD;
            }
        }

        printf("%lld\n", result);
    }

    return 0;
}