#include <stdio.h>
#include <stdlib.h>

#define MAXN 71
#define MAXH 301
#define MAXT 31

int n;
int heights[MAXN];
int thicknesses[MAXN];
int dp[MAXN][MAXH][MAXT];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &heights[i], &thicknesses[i]);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= MAXH; j++) {
            for (int k = 0; k <= MAXT; k++) {
                dp[i][j][k] = 0x3f3f3f3f;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= MAXH; j++) {
            for (int k = 0; k <= MAXT; k++) {
                if (dp[i-1][j][k] != 0x3f3f3f3f) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k]);
                    dp[i][max(j, heights[i-1])][k] = min(dp[i][max(j, heights[i-1])][k], dp[i-1][j][k] + thicknesses[i-1]);
                    dp[i][j][max(k, thicknesses[i-1])] = min(dp[i][j][max(k, thicknesses[i-1])], dp[i-1][j][k] + heights[i-1]);
                }
            }
        }
    }

    int min_s = 0x3f3f3f3f;
    for (int j = 0; j <= MAXH; j++) {
        for (int k = 0; k <= MAXT; k++) {
            if (dp[n][j][k] != 0x3f3f3f3f && dp[n][j][k] != 0) {
                min_s = min(min_s, (j * k));
            }
        }
    }

    printf("%d\n", min_s);

    return 0;
}