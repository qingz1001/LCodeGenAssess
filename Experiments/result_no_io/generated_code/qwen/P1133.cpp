#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n;
    scanf("%d", &n);

    int a[MAXN], b[MAXN], c[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &a[i], &b[i], &c[i]);
    }

    long long dp[2][3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dp[0][i][j] = dp[1][i][j] = -1;
        }
    }

    dp[0][0][1] = a[0];
    dp[0][1][0] = b[0];
    dp[0][1][2] = c[0];

    for (int i = 1; i < n; i++) {
        long long new_dp[2][3][3];
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (dp[0][j][k] == -1) continue;
                if (j != 0 && abs(j - 0) > 1) {
                    new_dp[0][0][k] = fmax(new_dp[0][0][k], dp[0][j][k] + a[i]);
                }
                if (j != 1 && abs(j - 1) > 1) {
                    new_dp[0][1][k] = fmax(new_dp[0][1][k], dp[0][j][k] + b[i]);
                }
                if (j != 2 && abs(j - 2) > 1) {
                    new_dp[0][2][k] = fmax(new_dp[0][2][k], dp[0][j][k] + c[i]);
                }
            }
        }
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (dp[1][j][k] == -1) continue;
                if (j != 0 && abs(j - 0) > 1) {
                    new_dp[1][0][k] = fmax(new_dp[1][0][k], dp[1][j][k] + a[i]);
                }
                if (j != 1 && abs(j - 1) > 1) {
                    new_dp[1][1][k] = fmax(new_dp[1][1][k], dp[1][j][k] + b[i]);
                }
                if (j != 2 && abs(j - 2) > 1) {
                    new_dp[1][2][k] = fmax(new_dp[1][2][k], dp[1][j][k] + c[i]);
                }
            }
        }
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                dp[0][j][k] = new_dp[0][j][k];
                dp[1][j][k] = new_dp[1][j][k];
            }
        }
    }

    printf("%lld\n", fmax(fmax(dp[0][0][0], dp[0][1][0]), dp[0][2][0]));

    return 0;
}