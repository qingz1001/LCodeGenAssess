#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    int row_count[MAX + 1] = {0}; // 记录每一行需要增加的通道数
    int col_count[MAX + 1] = {0}; // 记录每一列需要增加的通道数

    for (int i = 0; i < D; i++) {
        int X, Y, P, Q;
        scanf("%d %d %d %d", &X, &Y, &P, &Q);
        if (X == P) {
            // 同一行
            if (Y > Q) {
                int temp = Y;
                Y = Q;
                Q = temp;
            }
            col_count[Y]++;
        } else if (Y == Q) {
            // 同一列
            if (X > P) {
                int temp = X;
                X = P;
                P = temp;
            }
            row_count[X]++;
        }
    }

    // 对行和列的计数进行排序，找到最优的通道划分方案
    int row_sorted[MAX + 1], col_sorted[MAX + 1];
    for (int i = 1; i <= M; i++) {
        row_sorted[i] = row_count[i];
    }
    for (int i = 1; i <= N; i++) {
        col_sorted[i] = col_count[i];
    }
    qsort(row_sorted + 1, M, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(col_sorted + 1, N, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // 输出行通道
    printf("%d", row_sorted[M - K + 1]);
    for (int i = M - K + 2; i <= M; i++) {
        printf(" %d", row_sorted[i]);
    }
    printf("\n");

    // 输出列通道
    printf("%d", col_sorted[N - L + 1]);
    for (int i = N - L + 2; i <= N; i++) {
        printf(" %d", col_sorted[i]);
    }
    printf("\n");

    return 0;
}