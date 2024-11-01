#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

long long arr[MAXN];
long long sum[MAXN];
long long dp[MAXN];
long long maxn[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        sum[i] = sum[i - 1] + arr[i];
    }

    long long ans = 0;
    maxn[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = sum[i];
        for (int j = 0; j < i; j++) {
            if (maxn[j] < arr[i]) {
                dp[i] = (dp[i] > dp[j] + sum[i] - sum[j]) ? dp[i] : dp[j] + sum[i] - sum[j];
            }
        }
        maxn[i] = (maxn[i - 1] > arr[i]) ? maxn[i - 1] : arr[i];
        ans = (ans > dp[i]) ? ans : dp[i];
    }

    printf("%lld\n", n - ans);
    return 0;
}