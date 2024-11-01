#include <stdio.h>
#include <string.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    char grid[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i + j) % 2 == 0) {
                grid[i][j] = 'A';
            } else {
                grid[i][j] = 'B';
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}