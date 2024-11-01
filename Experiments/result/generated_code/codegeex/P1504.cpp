#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int heights[101][101] = {0};
    int max_height = 0;

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (1) {
            int height;
            scanf("%d", &height);
            if (height == -1) break;
            for (int k = j; k >= 0; k--) {
                heights[i][k + 1] = heights[i][k] + height;
            }
            j++;
        }
        max_height = (max_height > j) ? max_height : j;
    }

    int dp[10001] = {0};
    int total_height = 0;

    for (int i = 0; i < n; i++) {
        for (int j = total_height; j >= 0; j--) {
            for (int k = 0; k <= max_height; k++) {
                if (j >= heights[i][k]) {
                    dp[j] = (dp[j] > dp[j - heights[i][k]] + k) ? dp[j] : dp[j - heights[i][k]] + k;
                }
            }
        }
        total_height += max_height;
    }

    printf("%d\n", dp[total_height]);
    return 0;
}