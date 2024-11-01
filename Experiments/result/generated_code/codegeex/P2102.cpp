#include <stdio.h>
#include <string.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    char grid[N][M];

    // Initialize the grid with 'A'
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = 'A';
        }
    }

    // Check for conflicts and replace 'A' with 'B' if necessary
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i > 0 && grid[i-1][j] == 'B') || (j > 0 && grid[i][j-1] == 'B')) {
                grid[i][j] = 'B';
            }
        }
    }

    // Print the grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}