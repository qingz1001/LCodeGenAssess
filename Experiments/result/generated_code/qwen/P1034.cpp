#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXK 5

int n, k;
int points[MAXN][2];
int dp[MAXK][MAXN];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INT_MAX / 2;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n; j++) {
            int xmin = 501, ymin = 501, xmax = -1, ymax = -1;
            for (int l = j - 1; l >= i - 1; l--) {
                xmin = min(xmin, points[l][0]);
                ymin = min(ymin, points[l][1]);
                xmax = max(xmax, points[l][0]);
                ymax = max(ymax, points[l][1]);
                dp[i][j] = min(dp[i][j], dp[i - 1][l] + (xmax - xmin) * (ymax - ymin));
            }
        }
    }

    printf("%d\n", dp[k][n]);

    return 0;
}