#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

int n;
int value[MAXN][3];
int dp[MAXN][3][3];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &value[i][0], &value[i][1], &value[i][2]);
    }

    memset(dp, -INF, sizeof(dp));

    // Initialize the first position
    for (int j = 0; j < 3; j++) {
        dp[0][j][j] = value[0][j];
    }

    // Fill the dp table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (j != k && j != l) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][k][l] + value[i][j]);
                    }
                }
            }
        }
    }

    // Calculate the maximum value considering the circular nature
    int result = -INF;
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (j != k) {
                result = max(result, dp[n-1][j][k]);
            }
        }
    }

    printf("%d\n", result);
    return 0;
}