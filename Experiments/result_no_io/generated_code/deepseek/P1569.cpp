#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int main() {
    int n;
    int a[MAXN];
    int dp[MAXN];
    int sum[MAXN];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sum[0] = a[0];
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    if (sum[n - 1] < 0) {
        printf("Impossible\n");
        return 0;
    }

    dp[0] = (a[0] >= 0) ? 1 : 0;
    for (int i = 1; i < n; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            if (sum[i] - sum[j] >= 0) {
                dp[i] = (dp[j] + 1 > dp[i]) ? dp[j] + 1 : dp[i];
            }
        }
    }

    printf("%d\n", dp[n - 1]);
    return 0;
}