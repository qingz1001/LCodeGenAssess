#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int height;
    int left;
    int right;
} Platform;

int comparePlatforms(const void *a, const void *b) {
    return ((Platform *)b)->height - ((Platform *)a)->height;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    int x, y;
    scanf("%d %d", &x, &y);

    Platform platforms[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].height, &platforms[i].left, &platforms[i].right);
    }

    qsort(platforms, n, sizeof(Platform), comparePlatforms);

    int dp[n + 1];
    dp[n] = y;

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = INT_MAX;
        for (int j = i + 1; j <= n; j++) {
            if (platforms[i].height - (j == n ? 0 : platforms[j].height) <= h) {
                if (platforms[i].left <= x && x <= platforms[i].right) {
                    dp[i] = min(dp[i], dp[j] + platforms[i].height - (j == n ? 0 : platforms[j].height));
                }
                if (platforms[i].left <= x && x < platforms[i].right) {
                    dp[i] = min(dp[i], dp[j] + platforms[i].height - (j == n ? 0 : platforms[j].height) + platforms[i].right - x);
                }
                if (platforms[i].left < x && x <= platforms[i].right) {
                    dp[i] = min(dp[i], dp[j] + platforms[i].height - (j == n ? 0 : platforms[j].height) + x - platforms[i].left);
                }
            }
        }
    }

    printf("%d\n", dp[0]);

    return 0;
}