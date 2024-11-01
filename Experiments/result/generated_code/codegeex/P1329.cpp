#include <stdio.h>
#include <stdlib.h>

#define MOD 18446744073709551615ULL

typedef unsigned long long ull;

ull n, s, ans;
ull dp[105][105];

int main() {
    scanf("%llu%llu", &n, &s);

    dp[1][0] = 1;
    for (ull i = 2; i <= n; i++) {
        for (ull j = 0; j <= s; j++) {
            if (j >= i - 1) {
                dp[i][j] = dp[i - 1][j - (i - 1)] + dp[i - 1][j + (i - 1)];
                dp[i][j] %= MOD;
            } else {
                dp[i][j] = dp[i - 1][j + (i - 1)];
                dp[i][j] %= MOD;
            }
        }
    }

    printf("%llu\n", dp[n][s]);

    ull a[105];
    for (ull i = 0; i <= s; i++) {
        if (dp[n][i] > 0) {
            ull j = i;
            for (ull k = 1; k <= n; k++) {
                a[k] = j % 2;
                j /= 2;
            }
            for (ull k = 1; k <= n; k++) {
                printf("%d ", a[k] ? 1 : 0);
            }
            printf("\n");
        }
    }

    return 0;
}