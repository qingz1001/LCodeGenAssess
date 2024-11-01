#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 101
#define MAX_M 101
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int dp[MAX_N][MAX_M][2];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize dp array with a large value
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j][0] = dp[i][j][1] = INT_MAX;
        }
    }

    // Base case: no guests
    for (int j = 0; j < m; j++) {
        dp[0][j][0] = 0;
    }

    // Fill the dp table
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            // Not placing a guest in the current room
            dp[i][j][0] = MIN(dp[i][j][0], dp[i][(j-1+m)%m][0]);
            dp[i][j][0] = MIN(dp[i][j][0], dp[i][(j-1+m)%m][1]);

            // Placing a guest in the current room
            int anger = 0;
            if (dp[i-1][(j-1+m)%m][1] != INT_MAX) anger++;
            if (dp[i-1][(j+1)%m][1] != INT_MAX) anger++;

            if (dp[i-1][j][0] != INT_MAX) {
                dp[i][j][1] = MIN(dp[i][j][1], dp[i-1][j][0] + anger);
            }
        }
    }

    // Find the minimum anger sum
    int min_anger = INT_MAX;
    for (int j = 0; j < m; j++) {
        min_anger = MIN(min_anger, dp[n][j][0]);
        min_anger = MIN(min_anger, dp[n][j][1]);
    }

    printf("%d\n", min_anger);

    return 0;
}