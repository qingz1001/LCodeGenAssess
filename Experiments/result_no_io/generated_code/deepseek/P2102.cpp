#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    char grid[100][100];
    char colors[2] = {'B', 'W'};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = colors[(i + j) % 2];
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