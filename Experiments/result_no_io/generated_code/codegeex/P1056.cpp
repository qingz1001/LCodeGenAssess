#include <stdio.h>
#include <stdlib.h>

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    int row[M], col[N];
    for (int i = 0; i < M; i++) row[i] = 0;
    for (int i = 0; i < N; i++) col[i] = 0;

    for (int i = 0; i < D; i++) {
        int x, y, p, q;
        scanf("%d %d %d %d", &x, &y, &p, &q);
        if (x == p) {
            if (y < q) {
                row[x - 1]++;
            } else {
                row[p - 1]++;
            }
        } else if (y == q) {
            if (x < p) {
                col[y - 1]++;
            } else {
                col[q - 1]++;
            }
        }
    }

    int *row_sorted = (int *)malloc(M * sizeof(int));
    int *col_sorted = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < M; i++) row_sorted[i] = i;
    for (int i = 0; i < N; i++) col_sorted[i] = i;

    // Sorting rows by the number of students who will talk
    for (int i = 0; i < M - 1; i++) {
        for (int j = 0; j < M - i - 1; j++) {
            if (row[row_sorted[j]] < row[row_sorted[j + 1]]) {
                int temp = row_sorted[j];
                row_sorted[j] = row_sorted[j + 1];
                row_sorted[j + 1] = temp;
            }
        }
    }

    // Sorting columns by the number of students who will talk
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (col[col_sorted[j]] < col[col_sorted[j + 1]]) {
                int temp = col_sorted[j];
                col_sorted[j] = col_sorted[j + 1];
                col_sorted[j + 1] = temp;
            }
        }
    }

    // Output the best rows to open a channel
    for (int i = 0; i < K; i++) {
        printf("%d ", row_sorted[i] + 1);
    }
    printf("\n");

    // Output the best columns to open a channel
    for (int i = 0; i < L; i++) {
        printf("%d ", col_sorted[i] + 1);
    }
    printf("\n");

    free(row_sorted);
    free(col_sorted);

    return 0;
}