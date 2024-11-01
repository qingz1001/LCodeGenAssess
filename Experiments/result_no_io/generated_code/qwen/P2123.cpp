#include <stdio.h>
#include <stdlib.h>

#define MAXN 20001
#define LL long long

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        LL a[MAXN], b[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &a[i], &b[i]);
        }

        // Calculate the maximum bonus for each position
        LL dp[MAXN];
        dp[0] = a[0] + b[0];
        for (int i = 1; i < n; i++) {
            dp[i] = a[i] + b[i];
            if (dp[i - 1] > dp[i]) {
                dp[i] += dp[i - 1];
            }
        }

        // Find the minimum bonus among all positions
        LL min_bonus = dp[0];
        for (int i = 1; i < n; i++) {
            if (dp[i] < min_bonus) {
                min_bonus = dp[i];
            }
        }

        printf("%lld\n", min_bonus);
    }
    return 0;
}