#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_H 16

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, h;
    int f[MAX_N], d[MAX_N], t[MAX_N - 1];
    int dp[MAX_H * 60 / 5 + 1][MAX_N];

    scanf("%d", &n);
    scanf("%d", &h);
    h *= 60 / 5; // Convert hours to 5-minute intervals

    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &t[i]);
    }

    // Initialize dp array
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill dp array
    for (int i = 1; i <= h; i++) {
        for (int j = 0; j < n; j++) {
            int travel_time = 0;
            for (int k = 0; k < j; k++) {
                travel_time += t[k];
            }
            if (i < travel_time) break;

            int remaining_time = i - travel_time;
            int fish_caught = 0;
            int fish_rate = f[j];
            for (int k = 0; k < remaining_time; k++) {
                fish_caught += fish_rate;
                fish_rate = max(0, fish_rate - d[j]);
            }

            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
            dp[i][j] = max(dp[i][j], dp[i - travel_time][j] + fish_caught);
        }
    }

    printf("%d\n", dp[h][n - 1]);

    return 0;
}