#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXG 2000

int n, d, k;
long long s[MAXN];
long long dp[MAXG + 1][MAXN];

int main() {
    scanf("%d %d %lld", &n, &d, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &s[i], &s[i]);
    }

    for (int g = 0; g <= MAXG; g++) {
        for (int i = 1; i <= n; i++) {
            dp[g][i] = -1;
        }
    }

    dp[0][1] = 0;

    for (int g = 0; g <= MAXG; g++) {
        for (int i = 1; i <= n; i++) {
            if (dp[g][i] == -1) continue;
            for (int j = 1; j <= d + g && i + j <= n; j++) {
                dp[g][i + j] = dp[g][i + j] == -1 ? dp[g][i] + s[i + j] : fmin(dp[g][i + j], dp[g][i] + s[i + j]);
            }
        }
    }

    int ans = -1;
    for (int g = 0; g <= MAXG; g++) {
        if (dp[g][n] >= k) {
            ans = g;
            break;
        }
    }

    printf("%d\n", ans);

    return 0;
}