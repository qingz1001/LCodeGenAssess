#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int n;
    scanf("%d", &n);

    int matrix[MAX_N][MAX_N];
    int row_sum[MAX_N] = {0};
    int col_sum[MAX_N] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            row_sum[i] += matrix[i][j];
            col_sum[j] += matrix[i][j];
        }
    }

    int max_score = 0;
    int has_position = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                has_position = 1;
                int score = row_sum[i] + col_sum[j] - matrix[i][j];
                if (score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    if (has_position) {
        printf("%d\n", max_score);
    } else {
        printf("Bad Game!\n");
    }

    return 0;
}