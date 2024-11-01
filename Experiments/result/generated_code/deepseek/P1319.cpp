#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int *compressed_code = (int *)malloc(sizeof(int) * (2 * N * N));
    for (int i = 0; i < 2 * N * N; i++) {
        scanf("%d", &compressed_code[i]);
    }
    
    int **matrix = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * N);
    }
    
    int index = 0;
    int row = 0, col = 0;
    int is_zero = 1;
    
    for (int i = 1; i < 2 * N * N; i++) {
        int count = compressed_code[i];
        for (int j = 0; j < count; j++) {
            matrix[row][col] = is_zero ? 0 : 1;
            col++;
            if (col == N) {
                col = 0;
                row++;
            }
        }
        is_zero = !is_zero;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(compressed_code);
    
    return 0;
}