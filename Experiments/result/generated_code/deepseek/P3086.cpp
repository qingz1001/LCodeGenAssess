#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300

char marble[MAXN][MAXN];
int top_max[MAXN][MAXN];
int bottom_max[MAXN][MAXN];
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

    // Calculate top_max and bottom_max
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '.') {
                if (i == 0) {
                    top_max[i][j] = 1;
                } else {
                    top_max[i][j] = top_max[i-1][j] + 1;
                }
            } else {
                top_max[i][j] = 0;
            }
        }
    }

    for (int i = N-1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '.') {
                if (i == N-1) {
                    bottom_max[i][j] = 1;
                } else {
                    bottom_max[i][j] = bottom_max[i+1][j] + 1;
                }
            } else {
                bottom_max[i][j] = 0;
            }
        }
    }

    // Calculate left_most and right_most
    for (int i = 0; i < N; i++) {
        int left = -1;
        for (int j = 0; j < N; j++) {
            if (marble[i][j] == '*') {
                left = j;
            }
            left_most[i][j] = left;
        }
        int right = N;
        for (int j = N-1; j >= 0; j--) {
            if (marble[i][j] == '*') {
                right = j;
            }
            right_most[i][j] = right;
        }
    }

    int max_score = -1;

    // Try to find the best figure eight
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            if (marble[i][j] == '.') {
                int top_height = top_max[i][j];
                int bottom_height = bottom_max[i][j];

                for (int h = 1; h < top_height; h++) {
                    int top_row = i - h;
                    int left_top = left_most[top_row][j];
                    int right_top = right_most[top_row][j];

                    for (int b = 1; b < bottom_height; b++) {
                        int bottom_row = i + b;
                        int left_bottom = left_most[bottom_row][j];
                        int right_bottom = right_most[bottom_row][j];

                        int left = max(left_top, left_bottom);
                        int right = min(right_top, right_bottom);

                        if (left < j && right > j) {
                            int top_area = (right - left - 1) * h;
                            int bottom_area = (right - left - 1) * b;
                            int score = top_area * bottom_area;
                            if (score > max_score) {
                                max_score = score;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", max_score);

    return 0;
}