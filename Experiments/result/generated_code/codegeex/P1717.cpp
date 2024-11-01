#include <stdio.h>

int main() {
    int n, h;
    scanf("%d%d", &n, &h);

    int f[n + 1], d[n + 1], t[n];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i < n; i++) {
        scanf("%d", &t[i]);
    }

    int dp[17][n + 1][1001];
    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= 1000; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][0][0] = 0;

    for (int i = 0; i <= 16; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= 1000; k++) {
                if (dp[i][j][k] >= 0) {
                    if (j < n) {
                        int travel_time = 5 * t[j];
                        if (k + travel_time <= h * 60) {
                            dp[i + 1][j + 1][k + travel_time] = dp[i][j][k];
                        }
                    }
                    if (i < 16 && k + 5 <= h * 60) {
                        dp[i + 1][j][k + 5] = dp[i][j][k] + f[j] - d[j];
                    }
                }
            }
        }
    }

    int max_fish = 0;
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k <= h * 60; k++) {
            if (dp[16][i][k] > max_fish) {
                max_fish = dp[16][i][k];
            }
        }
    }

    printf("%d\n", max_fish);
    return 0;
}