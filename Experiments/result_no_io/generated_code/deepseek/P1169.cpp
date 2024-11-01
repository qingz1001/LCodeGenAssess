#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define MAXM 2000

int matrix[MAXN][MAXM];
int dp_square[MAXN][MAXM];
int dp_rect[MAXN][MAXM];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int max_square_area = 0;
    int max_rect_area = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 || j == 0) {
                dp_square[i][j] = 1;
                dp_rect[i][j] = 1;
            } else {
                if (matrix[i][j] != matrix[i-1][j] && matrix[i][j] != matrix[i][j-1] && matrix[i][j] != matrix[i-1][j-1]) {
                    dp_square[i][j] = min(dp_square[i-1][j-1], min(dp_square[i-1][j], dp_square[i][j-1])) + 1;
                } else {
                    dp_square[i][j] = 1;
                }

                int height = dp_rect[i-1][j] + 1;
                int width = dp_rect[i][j-1] + 1;
                if (matrix[i][j] != matrix[i-1][j]) {
                    height = 1;
                }
                if (matrix[i][j] != matrix[i][j-1]) {
                    width = 1;
                }
                dp_rect[i][j] = max(height, width);
            }

            max_square_area = max(max_square_area, dp_square[i][j] * dp_square[i][j]);
            max_rect_area = max(max_rect_area, dp_rect[i][j]);
        }
    }

    printf("%d\n%d\n", max_square_area, max_rect_area);

    return 0;
}