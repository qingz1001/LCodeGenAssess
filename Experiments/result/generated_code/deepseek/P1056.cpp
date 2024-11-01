#include <stdio.h>
#include <stdlib.h>

#define MAX_M 1000
#define MAX_N 1000

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    int row_count[MAX_M] = {0};
    int col_count[MAX_N] = {0};

    for (int i = 0; i < D; i++) {
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if (X == P) {
            int min_col = Y < Q ? Y : Q;
            col_count[min_col]++;
        } else {
            int min_row = X < P ? X : P;
            row_count[min_row]++;
        }
    }

    int row_indices[MAX_M];
    int col_indices[MAX_N];

    for (int i = 0; i < M; i++) {
        row_indices[i] = i;
    }
    for (int i = 0; i < N; i++) {
        col_indices[i] = i;
    }

    qsort(row_indices, M, sizeof(int), compare);
    qsort(col_indices, N, sizeof(int), compare);

    int selected_rows[K];
    int selected_cols[L];

    for (int i = 0; i < K; i++) {
        selected_rows[i] = row_indices[i];
    }
    for (int i = 0; i < L; i++) {
        selected_cols[i] = col_indices[i];
    }

    qsort(selected_rows, K, sizeof(int), compare);
    qsort(selected_cols, L, sizeof(int), compare);

    for (int i = 0; i < K; i++) {
        printf("%d", selected_rows[i]);
        if (i < K - 1) printf(" ");
    }
    printf("\n");

    for (int i = 0; i < L; i++) {
        printf("%d", selected_cols[i]);
        if (i < L - 1) printf(" ");
    }
    printf("\n");

    return 0;
}