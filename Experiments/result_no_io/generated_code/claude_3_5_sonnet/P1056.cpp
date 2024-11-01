#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int row[MAX_N], col[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    for (int i = 0; i < D; i++) {
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if (X == P) {
            col[Y < Q ? Y : Q]++;
        } else {
            row[X < P ? X : P]++;
        }
    }

    qsort(row, M - 1, sizeof(int), cmp);
    qsort(col, N - 1, sizeof(int), cmp);

    for (int i = 0; i < K; i++) {
        printf("%d", row[i]);
        if (i < K - 1) printf(" ");
    }
    printf("\n");

    for (int i = 0; i < L; i++) {
        printf("%d", col[i]);
        if (i < L - 1) printf(" ");
    }
    printf("\n");

    return 0;
}