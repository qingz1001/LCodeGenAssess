#include <stdio.h>
#include <string.h>

#define MAX_N 16
#define MAX_COLOR 20

struct Rectangle {
    int y1, x1, y2, x2, color;
};

struct Rectangle rectangles[MAX_N];
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

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int mask = 1; mask < (1 << N); mask++) {
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                int prev_mask = mask & ~(1 << i);
                if (can_paint(prev_mask, i)) {
                    int new_colors = color_mask[rectangles[i].color] & ~prev_mask;
                    dp[mask] = min(dp[mask], dp[prev_mask] + (new_colors ? 1 : 0));
                }
            }
        }
    }

    return dp[(1 << N) - 1];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &rectangles[i].y1, &rectangles[i].x1, &rectangles[i].y2, &rectangles[i].x2, &rectangles[i].color);
        color_mask[rectangles[i].color] |= (1 << i);
    }

    printf("%d\n", solve());
    return 0;
}