#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005
#define LL long long

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        LL a[MAXN], b[MAXN];
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld", &a[i], &b[i]);
        }

        LL dp[MAXN];
        dp[1] = a[1] + b[1];
        for (int i = 2; i <= n; ++i) {
            dp[i] = fmax(dp[i-1], a[i] * (i - 1)) + b[i];
        }

        printf("%lld\n", dp[n]);
    }
    return 0;
}