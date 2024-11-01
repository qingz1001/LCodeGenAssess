#include <stdio.h>
#include <limits.h>

#define MAX_POINTS 50
#define MAX_DIM 500

int n, k;
int points[MAX_POINTS][2];
int min_area = INT_MAX;

void coverPoints(int covered[MAX_DIM + 1][MAX_DIM + 1], int start_x, int start_y, int end_x, int end_y) {
    for (int i = start_x; i <= end_x; i++) {
        for (int j = start_y; j <= end_y; j++) {
            covered[i][j] = 1;
        }
    }
}

int isCovered(int covered[MAX_DIM + 1][MAX_DIM + 1]) {
    for (int i = 0; i <= MAX_DIM; i++) {
        for (int j = 0; j <= MAX_DIM; j++) {
            if (covered[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void calculateArea(int covered[MAX_DIM + 1][MAX_DIM + 1], int rectangles) {
    if (rectangles == k) {
        if (isCovered(covered)) {
            int area = 0;
            for (int i = 0; i <= MAX_DIM; i++) {
                for (int j = 0; j <= MAX_DIM; j++) {
                    if (covered[i][j] == 1) {
                        area++;
                    }
                }
            }
            if (area < min_area) {
                min_area = area;
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int min_x = points[i][0] < points[j][0] ? points[i][0] : points[j][0];
            int max_x = points[i][0] > points[j][0] ? points[i][0] : points[j][0];
            int min_y = points[i][1] < points[j][1] ? points[i][1] : points[j][1];
            int max_y = points[i][1] > points[j][1] ? points[i][1] : points[j][1];

            int new_covered[MAX_DIM + 1][MAX_DIM + 1];
            for (int a = 0; a <= MAX_DIM; a++) {
                for (int b = 0; b <= MAX_DIM; b++) {
                    new_covered[a][b] = covered[a][b];
                }
            }

            coverPoints(new_covered, min_x, min_y, max_x, max_y);
            calculateArea(new_covered, rectangles + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i][0], &points[i][1]);
    }

    int covered[MAX_DIM + 1][MAX_DIM + 1];
    for (int i = 0; i <= MAX_DIM; i++) {
        for (int j = 0; j <= MAX_DIM; j++) {
            covered[i][j] = 0;
        }
    }

    calculateArea(covered, 0);
    printf("%d\n", min_area);

    return 0;
}