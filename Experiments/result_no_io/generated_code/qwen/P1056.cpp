#include <stdio.h>
#include <stdlib.h>

#define MAX_M 1000
#define MAX_N 1000
#define MAX_D 2000

int main() {
    int M, N, K, L, D;
    scanf("%d %d %d %d %d", &M, &N, &K, &L, &D);

    int edges[MAX_D][4];
    for (int i = 0; i < D; i++) {
        scanf("%d %d %d %d", &edges[i][0], &edges[i][1], &edges[i][2], &edges[i][3]);
    }

    // Sort edges by the row and column of the first student
    qsort(edges, D, sizeof(edges[0]), [](const void *a, const void *b) {
        if (((int *)a)[0] != ((int *)b)[0]) return ((int *)a)[0] - ((int *)b)[0];
        else return ((int *)a)[1] - ((int *)b)[1];
    });

    // Find rows to cut
    int row_cut[MAX_M];
    int row_count = 0;
    for (int i = 0; i < D; i++) {
        if (edges[i][0] == edges[i + 1][0] && edges[i][1] + 1 == edges[i + 1][2]) {
            row_cut[row_count++] = edges[i][0] + 1;
            i++;
        }
    }

    // Sort edges by the row and column of the second student
    qsort(edges, D, sizeof(edges[0]), [](const void *a, const void *b) {
        if (((int *)a)[2] != ((int *)b)[2]) return ((int *)a)[2] - ((int *)b)[2];
        else return ((int *)a)[3] - ((int *)b)[3];
    });

    // Find columns to cut
    int col_cut[MAX_N];
    int col_count = 0;
    for (int i = 0; i < D; i++) {
        if (edges[i][2] == edges[i + 1][2] && edges[i][3] + 1 == edges[i + 1][1]) {
            col_cut[col_count++] = edges[i][2] + 1;
            i++;
        }
    }

    // Output the results
    printf("%d ", row_count);
    for (int i = 0; i < row_count; i++) {
        printf("%d", row_cut[i]);
        if (i < row_count - 1) printf(" ");
    }
    printf("\n");

    printf("%d ", col_count);
    for (int i = 0; i < col_count; i++) {
        printf("%d", col_cut[i]);
        if (i < col_count - 1) printf(" ");
    }
    printf("\n");

    return 0;
}