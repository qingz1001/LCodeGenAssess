#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
    }

    // Read the upper triangular part of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &M[i][j]);
            M[j][i] = M[i][j]; // Symmetric matrix
        }
        M[i][i] = 0; // Diagonal elements are zero
    }

    // Calculate the tree weight
    int weight = 0;
    for (int i = 1; i < n; i++) {
        int min_dist = M[0][i];
        for (int j = 1; j < i; j++) {
            int dist = (M[0][i] + M[0][j] - M[i][j]) / 2;
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        weight += min_dist;
    }

    printf("%d\n", weight);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);

    return 0;
}