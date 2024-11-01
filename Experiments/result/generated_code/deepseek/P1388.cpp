#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int calculate(int *nums, int start, int end) {
    int result = 0;
    for (int i = start; i <= end; i++) {
        result += nums[i];
    }
    return result;
}

int maxProduct(int *nums, int n, int k) {
    int dp[n][k + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INT_MIN;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][0] = calculate(nums, 0, i);
    }

    for (int j = 1; j <= k; j++) {
        for (int i = j; i < n; i++) {
            for (int m = j - 1; m < i; m++) {
                dp[i][j] = max(dp[i][j], dp[m][j - 1] * calculate(nums, m + 1, i));
            }
        }
    }

    return dp[n - 1][k];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    printf("%d\n", maxProduct(nums, n, k));
    return 0;
}