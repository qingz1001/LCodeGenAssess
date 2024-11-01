#include <stdio.h>
#include <stdlib.h>

#define MAX_N 16
#define MAX_COLOR 20

int n;
struct Rectangle {
    int x1, y1, x2, y2, color;
} rectangles[MAX_N];

int dp[MAX_N][MAX_COLOR + 1];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2, &rectangles[i].color);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= MAX_COLOR; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= MAX_COLOR; j++) {
            dp[i][j] = dp[i - 1][j];
            if (rectangles[i - 1].color == j) {
                dp[i][j]++;
            }
        }
    }

    int result = dp[n][1];
    for (int j = 2; j <= MAX_COLOR; j++) {
        result = (result > dp[n][j]) ? dp[n][j] : result;
    }

    printf("%d\n", result);

    return 0;
}