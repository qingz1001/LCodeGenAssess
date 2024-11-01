#include <stdio.h>
#include <string.h>

#define MAX_N 300
#define INF 0x3f3f3f3f

int n;
char grid[MAX_N][MAX_N];
int top_area[MAX_N][MAX_N], bottom_area[MAX_N][MAX_N];
int max_score = -1;

void calculate_areas() {
    int i, j;
    // Calculate top area
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] == '*') {
                top_area[i][j] = 0;
            } else if (i == 0 || j == 0) {
                top_area[i][j] = 0;
            } else {
                top_area[i][j] = top_area[i-1][j] + top_area[i][j-1] - top_area[i-1][j-1] + 1;
            }
        }
    }

    // Calculate bottom area
    for (i = n-1; i >= 0; i--) {
        for (j = n-1; j >= 0; j--) {
            if (grid[i][j] == '*') {
                bottom_area[i][j] = 0;
            } else if (i == n-1 || j == n-1) {
                bottom_area[i][j] = 0;
            } else {
                bottom_area[i][j] = bottom_area[i+1][j] + bottom_area[i][j+1] - bottom_area[i+1][j+1] + 1;
            }
        }
    }
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    calculate_areas();

    // Try to find the optimal figure eight
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] == '*' || grid[i][j] == '.') {
                int top_width = 0, bottom_width = 0;
                for (int k = j; k < n && grid[i][k] != '*'; k++) {
                    top_width++;
                }
                for (int k = j; k >= 0 && grid[i][k] != '*'; k--) {
                    bottom_width++;
                }
                if (top_width > 0 && bottom_width > 0) {
                    int top_height = 0, bottom_height = 0;
                    for (int k = i; k >= 0 && grid[k][j] != '*'; k--) {
                        top_height++;
                    }
                    for (int k = i; k < n && grid[k][j] != '*'; k++) {
                        bottom_height++;
                    }
                    if (top_height > 0 && bottom_height > 0) {
                        int top_total_area = top_width * top_height;
                        int bottom_total_area = bottom_width * bottom_height;
                        int common_area = 0;
                        for (int k = i - top_height + 1; k <= i; k++) {
                            if (grid[k][j] != '*') {
                                common_area += top_area[k][j] - top_area[k][j - top_width];
                            }
                        }
                        for (int k = i + 1; k < i + bottom_height; k++) {
                            if (grid[k][j] != '*') {
                                common_area += bottom_area[k][j] - bottom_area[k][j - bottom_width];
                            }
                        }
                        if (common_area > 0) {
                            int score = top_total_area * bottom_total_area;
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