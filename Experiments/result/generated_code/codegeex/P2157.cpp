#include <stdio.h>
#include <string.h>

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        int N;
        scanf("%d", &N);
        int T[1005], B[1005];
        for (int i = 1; i <= N; i++) {
            scanf("%d%d", &T[i], &B[i]);
        }

        int dp[1005][1 << 8];
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < (1 << 8); j++) {
                for (int k = i - 1; k >= 0 && k >= i - B[i - 1] - 1; k--) {
                    if (k > 0) {
                        dp[i][j] = (dp[i][j] < dp[k][j | (1 << (i - 1 - k))] + (T[i] ^ T[k])) ? dp[i][j] : (dp[k][j | (1 << (i - 1 - k))] + (T[i] ^ T[k]));
                    } else {
                        dp[i][j] = (dp[i][j] < dp[k][j | (1 << (i - 1 - k))] + T[i]) ? dp[i][j] : (dp[k][j | (1 << (i - 1 - k))] + T[i]);
                    }
                }
            }
        }

        int ans = 0x3f3f3f3f;
        for (int i = 0; i < (1 << 8); i++) {
            ans = (ans < dp[N][i]) ? ans : dp[N][i];
        }
        printf("%d\n", ans);
    }
    return 0;
}