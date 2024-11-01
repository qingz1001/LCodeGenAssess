#include <stdio.h>
#include <string.h>

#define MAX_N 51
#define MAX_LEVEL 1001

int n, beginLevel, maxLevel;
int changes[MAX_N];
int dp[MAX_N][MAX_LEVEL];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    for (int i = 0; i < n; i++) {
        scanf("%d", &changes[i]);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][beginLevel] = beginLevel;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= maxLevel; j++) {
            if (dp[i-1][j] != -1) {
                int up = j + changes[i-1];
                int down = j - changes[i-1];
                if (up <= maxLevel) {
                    dp[i][up] = max(dp[i][up], up);
                }
                if (down >= 0) {
                    dp[i][down] = max(dp[i][down], down);
                }
            }
        }
    }

    int result = -1;
    for (int j = 0; j <= maxLevel; j++) {
        result = max(result, dp[n][j]);
    }

    printf("%d\n", result);

    return 0;
}