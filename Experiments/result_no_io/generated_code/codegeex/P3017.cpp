#include <stdio.h>
#include <limits.h>

int main() {
    int R, C, A, B;
    scanf("%d%d%d%d", &R, &C, &A, &B);

    int grid[501][501] = {0};
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            int chips;
            scanf("%d", &chips);
            grid[i][j] = grid[i][j-1] + chips;
        }
    }

    int min[501][501] = {0};
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            int min_chips = INT_MAX;
            for (int k = 1; k < j; k++) {
                min_chips = (min_chips < grid[i][k] ? min_chips : grid[i][k]);
            }
            min[i][j] = min_chips;
        }
    }

    int dp[501][501] = {0};
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (i % A == 0 && j % B == 0) {
                int max_chips = 0;
                for (int k = 1; k <= i; k += A) {
                    for (int l = 1; l <= j; l += B) {
                        int chips = 0;
                        for (int m = k; m <= i; m++) {
                            chips += min[m][l];
                        }
                        max_chips = (max_chips > chips ? max_chips : chips);
                    }
                }
                dp[i][j] = max_chips;
            }
        }
    }

    int result = 0;
    for (int i = A; i <= R; i += A) {
        for (int j = B; j <= C; j += B) {
            result = (result > dp[i][j] ? result : dp[i][j]);
        }
    }

    printf("%d\n", result);
    return 0;
}