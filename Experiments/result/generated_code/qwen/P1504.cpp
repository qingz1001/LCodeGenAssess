#include <stdio.h>
#include <stdlib.h>

int max_height(int *heights, int n) {
    int *prefix_sum = (int *)malloc((n + 1) * sizeof(int));
    prefix_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + heights[i - 1];
    }

    int *dp = (int *)malloc(n * sizeof(int));
    dp[0] = heights[0];
    for (int i = 1; i < n; i++) {
        dp[i] = heights[i];
        for (int j = 0; j < i; j++) {
            if (prefix_sum[j + 1] - prefix_sum[i + 1 - j] >= prefix_sum[i + 1] - prefix_sum[j]) {
                dp[i] = heights[i] - (prefix_sum[i + 1] - prefix_sum[j]);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        if (result < dp[i]) {
            result = dp[i];
        }
    }

    free(prefix_sum);
    free(dp);

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int *heights = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int h;
        while (scanf("%d", &h) != EOF && h != -1) {
            heights[i] = h;
        }
    }

    printf("%d\n", max_height(heights, n));

    free(heights);

    return 0;
}