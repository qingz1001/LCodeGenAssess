#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_T 50
#define INF 1000000000

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int x1, y1, x2, y2, T;
    char winds[MAX_T];
    int dp[MAX_T + 1][MAX_T + 1][MAX_T + 1];

    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        scanf(" %c", &winds[i]);
    }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx + dy > T) {
        printf("-1\n");
        return 0;
    }

    for (int i = 0; i <= T; i++) {
        for (int j = 0; j <= T; j++) {
            for (int k = 0; k <= T; k++) {
                dp[i][j][k] = INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int t = 0; t < T; t++) {
        for (int x = 0; x <= T; x++) {
            for (int y = 0; y <= T; y++) {
                if (dp[t][x][y] == INF) continue;

                dp[t + 1][x][y] = min(dp[t + 1][x][y], dp[t][x][y]);

                if (winds[t] == 'E' && x < T) {
                    dp[t + 1][x + 1][y] = min(dp[t + 1][x + 1][y], dp[t][x][y] + 1);
                }
                if (winds[t] == 'W' && x > 0) {
                    dp[t + 1][x - 1][y] = min(dp[t + 1][x - 1][y], dp[t][x][y] + 1);
                }
                if (winds[t] == 'N' && y < T) {
                    dp[t + 1][x][y + 1] = min(dp[t + 1][x][y + 1], dp[t][x][y] + 1);
                }
                if (winds[t] == 'S' && y > 0) {
                    dp[t + 1][x][y - 1] = min(dp[t + 1][x][y - 1], dp[t][x][y] + 1);
                }
            }
        }
    }

    int result = dp[T][dx][dy];
    if (result == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}