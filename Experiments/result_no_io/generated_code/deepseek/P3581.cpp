#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1000005

int n, k, p;
int dislike[MAXN];
int dp[MAXN];

int main() {
    scanf("%d %d %d", &n, &k, &p);
    memset(dislike, 0, sizeof(dislike));

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        if (b - a <= p) {
            dislike[b] |= (1 << (b - a));
        }
    }

    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i > p + 1) {
            dp[i] = (dp[i] + dp[i - p - 1]) % MOD;
        }
        for (int j = 1; j <= p; j++) {
            if (i - j > 0 && (dislike[i] & (1 << j))) {
                dp[i] = (dp[i] - dp[i - j] + MOD) % MOD;
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}