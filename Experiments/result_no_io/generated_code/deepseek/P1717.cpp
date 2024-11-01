#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_TIME 960 // 16 hours * 60 minutes

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, h;
    int f[MAX_N], d[MAX_N], t[MAX_N - 1];
    int dp[MAX_N][MAX_TIME + 1];

    scanf("%d", &n);
    scanf("%d", &h);
    h *= 60; // convert hours to minutes

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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= h; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill dp array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= h; j++) {
            if (i == 0) {
                int time_left = j;
                int fish_caught = 0;
                int fish_rate = f[i];
                while (time_left >= 5 && fish_rate > 0) {
                    fish_caught += fish_rate;
                    time_left -= 5;
                    fish_rate -= d[i];
                }
                dp[i][j] = fish_caught;
            } else {
                int travel_time = 0;
                for (int k = 0; k < i; k++) {
                    travel_time += 5 * t[k];
                }
                if (j >= travel_time) {
                    int time_left = j - travel_time;
                    int fish_caught = 0;
                    int fish_rate = f[i];
                    while (time_left >= 5 && fish_rate > 0) {
                        fish_caught += fish_rate;
                        time_left -= 5;
                        fish_rate -= d[i];
                    }
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - travel_time] + fish_caught);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }

    printf("%d\n", dp[n - 1][h]);

    return 0;
}