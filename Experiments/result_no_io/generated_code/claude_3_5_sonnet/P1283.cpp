#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 16
#define MAX_COLOR 20

typedef struct {
    int y1, x1, y2, x2, color;
} Rectangle;

Rectangle rectangles[MAX_N];
int N;
int dp[1 << MAX_N];
int color_mask[MAX_COLOR + 1];

int can_paint(int mask, int i) {
    for (int j = 0; j < N; j++) {
        if ((mask & (1 << j)) && 
            rectangles[j].y2 > rectangles[i].y1 && 
            rectangles[j].x1 < rectangles[i].x2 && 
            rectangles[j].x2 > rectangles[i].x1) {
            return 0;
        }
    }
    return 1;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int mask) {
    if (mask == (1 << N) - 1) return 0;
    if (dp[mask] != -1) return dp[mask];

    int result = N;
    int used_colors[MAX_COLOR + 1] = {0};

    for (int i = 0; i < N; i++) {
        if (!(mask & (1 << i)) && can_paint(mask, i)) {
            int new_mask = mask | (1 << i);
            int color = rectangles[i].color;
            
            if (!used_colors[color]) {
                used_colors[color] = 1;
                result = min(result, 1 + solve(new_mask));
            } else {
                result = min(result, solve(new_mask));
            }
        }
    }

    return dp[mask] = result;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &rectangles[i].y1, &rectangles[i].x1, 
              &rectangles[i].y2, &rectangles[i].x2, &rectangles[i].color);
    }

    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0));

    return 0;
}