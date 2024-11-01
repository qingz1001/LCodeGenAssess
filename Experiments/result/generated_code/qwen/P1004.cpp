#include <stdio.h>
#define MAXN 10

int grid[MAXN][MAXN];
int dp[MAXN][MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int N, x, y, value;
    scanf("%d", &N);
    while (scanf("%d %d %d", &x, &y, &value) == 3 && !(x == 0 && y == 0)) {
        grid[x - 1][y - 1] = value;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = grid[0][0];
            } else {
                if (i > 0) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] + grid[i][j]);
                }
                if (j > 0) {
                    dp[i][j] = max(dp[i][j], dp[i][j - 1] + grid[i][j]);
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dp[i][j] != 0) {
                int remaining_sum = 0;
                for (int k = i; k < N; k++) {
                    for (int l = j; l < N; l++) {
                        remaining_sum += grid[k][l];
                    }
                }
                result = max(result, dp[i][j] + remaining_sum);
            }
        }
    }

    printf("%d\n", result);

    return 0;
}