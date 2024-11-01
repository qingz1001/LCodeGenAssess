#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int n, k, p;
int dislike[100005][2];
int dp[100005][4];

int main() {
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &dislike[i][0], &dislike[i][1]);
        dislike[i][0]--;
        dislike[i][1]--;
    }

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][3]) % MOD;
        if (p == 1) {
            dp[i][1] = (dp[i-1][0] + dp[i-1][2] + dp[i-1][3]) % MOD;
            dp[i][2] = 0;
            dp[i][3] = 0;
        } else if (p == 2) {
            dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD;
            dp[i][2] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][3]) % MOD;
            dp[i][3] = 0;
        } else {
            dp[i][1] = dp[i-1][0];
            dp[i][2] = (dp[i-1][0] + dp[i-1][1]) % MOD;
            dp[i][3] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) % MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i < k; i++) {
        int a = dislike[i][0];
        int b = dislike[i][1];
        if (b == n-1) {
            dp[n][3] = 0;
        } else if (a == n-1) {
            dp[n][2] = 0;
        }
    }

    ans = (dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3]) % MOD;
    printf("%d\n", ans);
    return 0;
}