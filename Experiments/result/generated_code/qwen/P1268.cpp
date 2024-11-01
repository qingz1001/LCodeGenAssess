#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int M[n][n];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            scanf("%d", &M[i][j]);
        }
    }

    int total_weight = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            total_weight += M[i][j];
        }
    }

    printf("%d\n", total_weight);

    return 0;
}