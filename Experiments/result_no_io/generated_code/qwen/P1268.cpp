#include <stdio.h>
#include <stdlib.h>

#define MAXN 30

int main() {
    int n;
    scanf("%d", &n);

    int M[MAXN][MAXN];
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            scanf("%d", &M[i][j]);
        }
    }

    int total_weight = 0;

    // Use a simple approach to calculate the total weight of the tree
    // by summing up all non-zero elements in the upper triangle of the matrix.
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (M[i][j] != 0) {
                total_weight += M[i][j];
            }
        }
    }

    printf("%d\n", total_weight);

    return 0;
}