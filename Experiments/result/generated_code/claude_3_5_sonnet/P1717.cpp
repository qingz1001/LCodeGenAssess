#include <stdio.h>
#include <string.h>

#define MAX_N 25
#define MAX_H 16

int n, h;
int f[MAX_N], d[MAX_N], t[MAX_N];
int dp[MAX_N][MAX_H * 12 + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    scanf("%d", &h);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &t[i]);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    int total_time = h * 12;  // Convert hours to 5-minute intervals

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= total_time; j++) {
            if (dp[i][j] == -1) continue;

            // Stay and fish
            for (int k = 1; j + k <= total_time; k++) {
                int fish = max(0, f[i] - (k - 1) * d[i]);
                int new_fish = dp[i][j] + fish;
                dp[i][j + k] = max(dp[i][j + k], new_fish);
            }

            // Move to next lake
            if (i < n - 1 && j + t[i] <= total_time) {
                dp[i + 1][j + t[i]] = max(dp[i + 1][j + t[i]], dp[i][j]);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= total_time; j++) {
            result = max(result, dp[i][j]);
        }
    }

    printf("%d\n", result);

    return 0;
}