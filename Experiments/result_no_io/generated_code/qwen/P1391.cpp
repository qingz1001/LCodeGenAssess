#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    int changes = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            if (i > 0 && i < n - 1 && j > 0 && j < n - 1) {
                int count = 0;
                count += matrix[i - 1][j];
                count += matrix[i + 1][j];
                count += matrix[i][j - 1];
                count += matrix[i][j + 1];
                if (count % 2 != 0) {
                    changes++;
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("-1\n");
    } else {
        printf("%d\n", changes);
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}