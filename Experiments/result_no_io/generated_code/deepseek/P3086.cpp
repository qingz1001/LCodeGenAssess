#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300

char marble[MAXN][MAXN];
int top_area[MAXN][MAXN];
int bottom_area[MAXN][MAXN];
int left_most[MAXN][MAXN];
int right_most[MAXN][MAXN];
int N;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", marble[i]);
    }

    // Calculate top_area
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '.') {
                if (i == 0) {
                    top_area[i][j] = 1;
                } else {
                    top_area[i][j] = top_area[i-1][j] + 1;
                }
            } else {
                top_area[i][j] = 0;
            }
        }
    }

    // Calculate bottom_area
    for (int i = N-1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '.') {
                if (i == N-1) {
                    bottom_area[i][j] = 1;
                } else {
                    bottom_area[i][j] = bottom_area[i+1][j] + 1;
                }
            } else {
                bottom_area[i][j] = 0;
            }
        }
    }

    // Calculate left_most and right_most
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '.') {
                if (j == 0) {
                    left_most[i][j] = j;
                } else {
                    left_most[i][j] = (marble[i][j-1] == '.') ? left_most[i][j-1] : j;
                }
            }
        }
        for (int j = N-1; j >= 0; j--) {
            if (marble[i][j] == '.') {
                if (j == N-1) {
                    right_most[i][j] = j;
                } else {
                    right_most[i][j] = (marble[i][j+1] == '.') ? right_most[i][j+1] : j;
                }
            }
        }
    }

    int max_score = -1;

    // Try every possible top rectangle
    for (int top_row = 0; top_row < N; top_row++) {
        for (int bottom_row = top_row; bottom_row < N; bottom_row++) {
            int left = -1, right = -1;
            for (int col = 0; col < N; col++) {
                if (top_area[bottom_row][col] > bottom_row - top_row) {
                    if (left == -1) left = col;
                    right = col;
                } else {
                    if (left != -1 && right != -1) {
                        int top_width = right - left + 1;
                        int top_height = bottom_row - top_row + 1;
                        int top_rect_area = top_width * top_height;

                        // Try every possible bottom rectangle
                        for (int bottom_top_row = bottom_row + 1; bottom_top_row < N; bottom_top_row++) {
                            int bottom_left = left_most[bottom_top_row][right];
                            int bottom_right = right_most[bottom_top_row][left];
                            if (bottom_left <= left && bottom_right >= right) {
                                int bottom_width = right - left + 1;
                                int bottom_height = bottom_area[bottom_top_row][left];
                                int bottom_rect_area = bottom_width * bottom_height;

                                max_score = max(max_score, top_rect_area * bottom_rect_area);
                            }
                        }
                    }
                    left = -1;
                    right = -1;
                }
            }
        }
    }

    printf("%d\n", max_score);
    return 0;
}