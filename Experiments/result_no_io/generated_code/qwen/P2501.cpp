#include <stdio.h>
#include <stdlib.h>

#define MAXN 35005

int n;
int a[MAXN];
int dp[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // Initialize dp array
    for (int i = 1; i <= n; i++) {
        dp[i] = a[i];
    }

    // Dynamic programming to find the minimum number of changes
    for (int i = 2; i <= n; i++) {
        if (dp[i] <= dp[i - 1]) {
            dp[i] = dp[i - 1] + 1;
        }
    }

    int min_changes = dp[n];

    // Find the minimum sum of absolute differences
    int sum_diff = 0;
    for (int i = 2; i <= n; i++) {
        if (dp[i] > dp[i - 1]) {
            sum_diff += dp[i] - dp[i - 1];
        }
    }

    printf("%d\n", min_changes);
    printf("%d\n", sum_diff);

    return 0;
}