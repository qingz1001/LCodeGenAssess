#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long dp[MAX_N][3][2];
int value[MAX_N][3];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &value[i][0], &value[i][1], &value[i][2]);
    }

    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            dp[0][i][j] = value[0][i];
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (j == k) continue;
                for (int l = 0; l < 2; l++) {
                    if (dp[i-1][k][l] == -1) continue;
                    long long newValue = dp[i-1][k][l] + value[i][j];
                    if (i == n-1) {
                        if ((j > k && k > value[0][l]) || (j < k && k < value[0][l])) {
                            dp[i][j][l] = MAX(dp[i][j][l], newValue);
                        }
                    } else {
                        dp[i][j][l] = MAX(dp[i][j][l], newValue);
                    }
                }
            }
        }
    }

    long long maxValue = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            maxValue = MAX(maxValue, dp[n-1][i][j]);
        }
    }

    printf("%lld\n", maxValue);

    return 0;
}