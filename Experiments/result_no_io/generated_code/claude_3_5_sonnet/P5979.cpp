#include <stdio.h>
#include <string.h>

#define MAX_N 1000001
#define MOD 1000000007

int n;
int c[MAX_N], d[MAX_N];
int dp[MAX_N], cnt[MAX_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &c[i], &d[i]);
    }

    dp[0] = 0;
    cnt[0] = 1;

    for (int i = 1; i <= n; i++) {
        dp[i] = -1;
        for (int j = i - 1; j >= 0 && i - j <= d[i]; j--) {
            if (i - j >= c[i] && dp[j] != -1) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                } else if (dp[j] + 1 == dp[i]) {
                    cnt[i] = (cnt[i] + cnt[j]) % MOD;
                }
            }
        }
    }

    if (dp[n] == -1) {
        printf("NIE\n");
    } else {
        printf("%d %d\n", dp[n], cnt[n]);
    }

    return 0;
}