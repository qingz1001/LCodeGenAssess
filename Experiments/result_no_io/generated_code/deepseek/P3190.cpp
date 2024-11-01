#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 100
#define MAXM 6
#define MAX_STATES (1 << (MAXM * 2))

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][MAX_STATES];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(dp, 0x80, sizeof(dp)); // Initialize dp array to a very small value
    dp[0][0][0] = 0; // Starting point

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int state = 0; state < (1 << (m * 2)); state++) {
                if (dp[i][j][state] == INT_MIN) continue;

                int new_state = (state << 2) & ((1 << (m * 2)) - 1);

                // Move right
                if (j + 1 < m) {
                    dp[i][j + 1][new_state] = max(dp[i][j + 1][new_state], dp[i][j][state]);
                }

                // Move down
                if (i + 1 < n) {
                    dp[i + 1][j][new_state] = max(dp[i + 1][j][new_state], dp[i][j][state]);
                }

                // Stay and enjoy the current cell
                int new_state_enjoy = new_state | (1 << (j * 2));
                dp[i][j][new_state_enjoy] = max(dp[i][j][new_state_enjoy], dp[i][j][state] + grid[i][j]);
            }
        }
    }

    int result = INT_MIN;
    for (int state = 0; state < (1 << (m * 2)); state++) {
        result = max(result, dp[n - 1][m - 1][state]);
    }

    printf("%d\n", result);
    return 0;
}