#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int max_intercept(int heights[], int n) {
    if (n == 0) return 0;
    int dp[n];
    for (int i = 0; i < n; i++) dp[i] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (heights[j] < heights[i]) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
    }
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max) max = dp[i];
    }
    return max;
}

int min_systems(int heights[], int n, int max_height) {
    int count = 0;
    int current_max = 0;
    for (int i = 0; i < n; i++) {
        if (heights[i] > current_max) {
            count++;
            current_max = heights[i];
        } else {
            for (int j = 0; j < n; j++) {
                if (heights[j] < heights[i] && heights[j] >= current_max - max_height) {
                    current_max = heights[j];
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    int heights[MAXN];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int max_intercept_count = max_intercept(heights, n);
    int min_systems_count = min_systems(heights, n, 50000);

    printf("%d\n", max_intercept_count);
    printf("%d\n", min_systems_count);

    return 0;
}