#include <stdio.h>
#include <stdlib.h>

#define MAX_N 16
#define MAX_C 21

int rectangles[MAX_N][5];
int dp[MAX_N + 1][MAX_C];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &rectangles[i][0], &rectangles[i][1], &rectangles[i][2], &rectangles[i][3], &rectangles[i][4]);
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 1; j < MAX_C; j++) {
            dp[i][j] = INT_MAX / 2;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        int color = rectangles[i - 1][4];
        for (int j = 0; j < MAX_C; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= color) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - color] + 1);
            }
        }
    }

    printf("%d\n", dp[N][0]);

    return 0;
}