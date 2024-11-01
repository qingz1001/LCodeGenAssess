#include <stdio.h>
#include <string.h>

int dp[1005][128];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int t[1005], b[1005];
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &t[i], &b[i]);
        }
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int s = 0; s < (1 << b[i]); s++) {
                for (int j = i; j <= i + b[i] && j <= n; j++) {
                    int next_s = s | (1 << (j - i));
                    if (j == i) {
                        dp[j][next_s] = 0;
                    } else {
                        dp[j][next_s] = dp[i - 1][s] + (j > 1 ? (t[j] ^ t[j - 1]) : 0);
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int s = 0; s < (1 << n); s++) {
            for (int i = n; i >= 1; i--) {
                if ((s & (1 << (i - 1))) == 0) {
                    ans = ans < dp[i][s] ? ans : dp[i][s];
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}