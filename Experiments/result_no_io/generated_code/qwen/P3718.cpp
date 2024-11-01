#include <stdio.h>
#include <string.h>

#define MAXN 100005

int main() {
    int n, k;
    char lights[MAXN];
    scanf("%d %d", &n, &k);
    scanf("%s", lights);

    int dp[n + 1][2];
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = dp[i][1] = n;
    }
    dp[0][0] = dp[0][1] = 0;

    for (int i = 1; i <= n; ++i) {
        if (lights[i - 1] == 'N') {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1] + 1;
        } else {
            dp[i][0] = dp[i - 1][1] + 1;
            dp[i][1] = dp[i - 1][0];
        }
    }

    int ans = n;
    for (int i = 0; i <= n; ++i) {
        ans = (ans < dp[i][0]) ? ans : dp[i][0];
    }

    printf("%d\n", ans);

    return 0;
}