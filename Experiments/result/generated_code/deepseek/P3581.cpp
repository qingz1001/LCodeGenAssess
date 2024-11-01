#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1000005

int n, k, p;
int dislikes[MAXN];
int dp[MAXN];

int main() {
    scanf("%d %d %d", &n, &k, &p);
    memset(dislikes, 0, sizeof(dislikes));

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }
        if (b - a <= p) {
            dislikes[b] |= (1 << (a - (b - p)));
        }
    }

    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        for (int j = 1; j <= p + 1; j++) {
            if (i - j > 0 && !(dislikes[i] & (1 << (j - 1)))) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}