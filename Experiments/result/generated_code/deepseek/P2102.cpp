#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    char grid[100][100];
    char current_char = 'A';

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i > 0 && grid[i-1][j] == current_char) {
                current_char = (current_char == 'A') ? 'B' : 'A';
            }
            if (j > 0 && grid[i][j-1] == current_char) {
                current_char = (current_char == 'A') ? 'B' : 'A';
            }
            grid[i][j] = current_char;
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