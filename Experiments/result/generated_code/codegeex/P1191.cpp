#include <stdio.h>
#include <string.h>

#define MAXN 151

char grid[MAXN][MAXN];
int n, heights[MAXN][MAXN], left[MAXN][MAXN], right[MAXN][MAXN];
int ans;

void preprocess() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'W') {
                heights[i][j] = heights[i-1][j] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int min_left = n, min_right = n;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'W') {
                min_left = j;
            } else {
                left[i][j] = min_left;
            }
        }
        for (int j = n-1; j >= 0; j--) {
            if (grid[i][j] == 'W') {
                min_right = j;
            } else {
                right[i][j] = min_right;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    preprocess();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'W') {
                for (int h = 1; h <= heights[i][j]; h++) {
                    int width = right[i][j] - left[i][j] + 1;
                    ans += width * h;
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}