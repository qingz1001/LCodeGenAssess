#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 1005
#define MAXB 8

int dp[MAXN][1 << MAXB][MAXB];
int T[MAXN], B[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &T[i], &B[i]);
        }

        memset(dp, 0x3f, sizeof(dp));
        dp[0][0][7] = 0;

        for (int i = 0; i < N; i++) {
            for (int mask = 0; mask < (1 << 8); mask++) {
                for (int k = -8; k <= 7; k++) {
                    if (dp[i][mask][k + 8] == 0x3f3f3f3f) continue;
                    if (mask & 1) {
                        dp[i + 1][mask >> 1][k + 7] = min(dp[i + 1][mask >> 1][k + 7], dp[i][mask][k + 8]);
                    } else {
                        int r = INT_MAX;
                        for (int j = 0; j <= 7; j++) {
                            if (mask & (1 << j)) continue;
                            if (i + j > r) break;
                            r = min(r, i + j + B[i + j]);
                            int cost = (i + k >= 0 ? (T[i + k] ^ T[i + j]) - (T[i + k] & T[i + j]) : 0);
                            dp[i][mask | (1 << j)][j + 8] = min(dp[i][mask | (1 << j)][j + 8], dp[i][mask][k + 8] + cost);
                        }
                    }
                }
            }
        }

        int ans = INT_MAX;
        for (int k = -8; k <= 0; k++) {
            ans = min(ans, dp[N][0][k + 8]);
        }
        printf("%d\n", ans);
    }
    return 0;
}