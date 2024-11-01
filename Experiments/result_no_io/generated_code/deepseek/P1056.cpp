#include <stdio.h>
#include <stdlib.h>

#define MAX_M 1000
#define MAX_N 1000

typedef struct {
    int count;
    int index;
} Pair;

int compare(const void *a, const void *b) {
    return ((Pair *)b)->count - ((Pair *)a)->count;
}

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    Pair row[MAX_M];
    Pair col[MAX_N];

    for (int i = 0; i < M; i++) {
        row[i].count = 0;
        row[i].index = i + 1;
    }
    for (int i = 0; i < N; i++) {
        col[i].count = 0;
        col[i].index = i + 1;
    }

    for (int i = 0; i < D; i++) {
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if (X == P) {
            int min_col = Y < Q ? Y : Q;
            col[min_col - 1].count++;
        } else {
            int min_row = X < P ? X : P;
            row[min_row - 1].count++;
        }
    }

    qsort(row, M, sizeof(Pair), compare);
    qsort(col, N, sizeof(Pair), compare);

    int selected_rows[K];
    int selected_cols[L];

    for (int i = 0; i < K; i++) {
        selected_rows[i] = row[i].index;
    }
    for (int i = 0; i < L; i++) {
        selected_cols[i] = col[i].index;
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