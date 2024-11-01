#include <stdio.h>
#include <stdlib.h>

#define MOD 18446744073709551615ULL

typedef unsigned long long ull;

ull dp[105][2005];

int main() {
    int n;
    ull s;
    scanf("%d%llu", &n, &s);

    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= s; j++) {
            if (j - 1 >= 0) {
                dp[i + 1][j] += dp[i][j - 1];
            }
            if (j + 1 <= s) {
                dp[i + 1][j] += dp[i][j + 1];
            }
            dp[i + 1][j] %= MOD;
        }
    }

    printf("%llu\n", dp[n][s]);

    int count = 0;
    for (int i = 0; i <= s; i++) {
        if (dp[n][s] == dp[n][i]) {
            printf("%d\n", i);
            count++;
            if (count == 100) {
                break;
            }
        }
    }

    return 0;
}