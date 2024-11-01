#include <stdio.h>
#include <string.h>

#define MAX_N 1001

int n;
int dp[MAX_N];
int cnt[MAX_N];

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    cnt[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            if (dp[j - i] + 1 < dp[j]) {
                dp[j] = dp[j - i] + 1;
                cnt[j] = cnt[j - i];
            } else if (dp[j - i] + 1 == dp[j]) {
                cnt[j] += cnt[j - i];
            }
        }
    }

    printf("%d %d\n", dp[n], cnt[n]);
}

int main() {
    scanf("%d", &n);
    solve();
    return 0;
}