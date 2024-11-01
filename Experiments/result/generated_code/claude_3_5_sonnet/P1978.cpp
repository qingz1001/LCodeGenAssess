#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000

int cmp(const void *a, const void *b) {
    return (*(long long*)a > *(long long*)b) - (*(long long*)a < *(long long*)b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    long long a[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a, n, sizeof(long long), cmp);

    int dp[MAX_N];
    memset(dp, 0, sizeof(dp));

    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] % a[i] != 0 || a[j] / a[i] >= k) {
                dp[i] = (dp[i] > dp[j] + 1) ? dp[i] : (dp[j] + 1);
            }
        }
        ans = (ans > dp[i]) ? ans : dp[i];
    }

    printf("%d\n", ans);

    return 0;
}