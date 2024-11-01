#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000

int matrix[MAX_N][MAX_M];
int n, m;

int is_symmetric(int row, int col, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[row+i][col+j] != matrix[row+size-1-i][col+j] ||
                matrix[row+i][col+j] != matrix[row+i][col+size-1-j] ||
                matrix[row+i][col+j] != matrix[row+size-1-i][col+size-1-j]) {
                return 0;
            }
        }
    }
    return 1;
}

int count_symmetric_squares() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int max_size = (n - i < m - j) ? n - i : m - j;
            for (int size = 1; size <= max_size; size++) {
                if (is_symmetric(i, j, size)) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int result = count_symmetric_squares();
    printf("%d\n", result);
    
    return 0;
}