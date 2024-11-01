#include <stdio.h>
#include <stdlib.h>

int countWhiteRectangles(int n, char **matrix) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'W') {
                for (int k = i + 1; k < n; k++) {
                    if (matrix[k][j] != 'W') break;
                    for (int l = j + 1; l < n; l++) {
                        if (matrix[i][l] != 'W' || matrix[k][l] != 'W') break;
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    char **matrix = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (char *)malloc(n * sizeof(char));
        scanf("%s", matrix[i]);
    }

    int result = countWhiteRectangles(n, matrix);

    printf("%d\n", result);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}