#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int matrix[N][N];
int row_sum[N], col_sum[N], diag_sum[2];
int known_count = 0;

int dfs(int pos) {
    if (pos == N * N) {
        int sum;
        for (int i = 0; i < N; i++) {
            sum = 0;
            for (int j = 0; j < N; j++) {
                sum += matrix[i][j];
            }
            if (sum != row_sum[i]) return 0;
        }
        for (int j = 0; j < N; j++) {
            sum = 0;
            for (int i = 0; i < N; i++) {
                sum += matrix[i][j];
            }
            if (sum != col_sum[j]) return 0;
        }
        sum = 0;
        for (int i = 0; i < N; i++) {
            sum += matrix[i][i];
        }
        if (sum != diag_sum[0]) return 0;
        sum = 0;
        for (int i = 0; i < N; i++) {
            sum += matrix[i][N-1-i];
        }
        if (sum != diag_sum[1]) return 0;
        return 1;
    }

    int i = pos / N, j = pos % N;
    if (matrix[i][j] != 0) {
        return dfs(pos + 1);
    }

    for (int num = 1; num <= 300; num++) {
        matrix[i][j] = num;
        if (dfs(pos + 1)) return 1;
    }
    matrix[i][j] = 0;
    return 0;
}

int main() {
    for (int i = 0; i < N; i++) {
        scanf("%d", &row_sum[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &col_sum[i]);
    }
    scanf("%d %d", &diag_sum[0], &diag_sum[1]);

    memset(matrix, 0, sizeof(matrix));
    for (int k = 0; k < N; k++) {
        int i, j, val;
        scanf("%d %d %d", &i, &j, &val);
        matrix[i][j] = val;
        known_count++;
    }

    if (dfs(0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}