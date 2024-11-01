#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_T 50
#define MAX_COORD 100

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int x1, y1, x2, y2, T;
    char winds[MAX_T + 1];
    int dp[MAX_T + 1][MAX_COORD * 2 + 1][MAX_COORD * 2 + 1];

    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        scanf(" %c", &winds[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][x1 + MAX_COORD][y1 + MAX_COORD] = 0;

    for (int t = 1; t <= T; t++) {
        for (int x = 0; x <= MAX_COORD * 2; x++) {
            for (int y = 0; y <= MAX_COORD * 2; y++) {
                int prev_x = x, prev_y = y;
                switch (winds[t-1]) {
                    case 'E': prev_x--; break;
                    case 'W': prev_x++; break;
                    case 'N': prev_y--; break;
                    case 'S': prev_y++; break;
                }
                if (prev_x >= 0 && prev_x <= MAX_COORD * 2 && prev_y >= 0 && prev_y <= MAX_COORD * 2) {
                    dp[t][x][y] = min(dp[t][x][y], dp[t-1][prev_x][prev_y] + 1);
                }
                dp[t][x][y] = min(dp[t][x][y], dp[t-1][x][y]);
            }
        }
    }

    int result = INT_MAX;
    for (int t = 0; t <= T; t++) {
        result = min(result, dp[t][x2 + MAX_COORD][y2 + MAX_COORD]);
    }

    if (result == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}