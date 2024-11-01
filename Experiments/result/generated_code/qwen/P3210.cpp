#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n;
long long a[MAXN];
long long dp[2][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }

    dp[0][0] = 0;
    dp[1][0] = 0;

    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) continue;
        for (int j = 0; j < i; ++j) {
            dp[0][i] = fmax(dp[0][i], dp[1][j] + a[i]);
            dp[1][i] = fmax(dp[1][i], dp[0][j] + a[i]);
        }
    }

    printf("%lld %lld\n", dp[0][n], dp[1][n]);

    return 0;
}