#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int main() {
    int n;
    scanf("%d", &n);

    int matrix[MAXN][MAXN];
    int row_sum[MAXN] = {0};
    int col_sum[MAXN] = {0};
    int total_sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] > 0) {
                row_sum[i] += matrix[i][j];
                col_sum[j] += matrix[i][j];
                total_sum += matrix[i][j];
            }
        }
    }

    int max_score = 0;
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

    if (max_score == 0) {
        printf("Bad Game!\n");
    } else {
        printf("%d\n", max_score);
    }

    return 0;
}