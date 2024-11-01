#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int matrix[N][N];
    int row = 0, col = 0;
    int value = 0; // 0 for 0, 1 for 1
    
    while (1) {
        int count;
        if (scanf("%d", &count) != 1) break;
        
        for (int i = 0; i < count; i++) {
            matrix[row][col] = value;
            col++;
            if (col == N) {
                col = 0;
                row++;
            }
        }
        
        value = 1 - value; // toggle between 0 and 1
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}