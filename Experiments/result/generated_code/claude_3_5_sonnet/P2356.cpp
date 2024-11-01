#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n;
    int matrix[MAX_N][MAX_N];
    int row_sum[MAX_N] = {0};
    int col_sum[MAX_N] = {0};
    int max_score = 0;
    int has_empty_space = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 0) {
                has_empty_space = 1;
            }
            row_sum[i] += matrix[i][j];
            col_sum[j] += matrix[i][j];
        }
    }

    if (!has_empty_space) {
        printf("Bad Game!\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                int score = row_sum[i] + col_sum[j];
                if (score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    printf("%d\n", max_score);

    return 0;
}