#include <stdio.h>
#include <stdlib.h>

#define MAX_R 10
#define MAX_C 10

int R, C;
char map[MAX_R][MAX_C];

int is_dead_end(int r, int c) {
    int count = 0;
    if (r > 0 && map[r - 1][c] == '.') count++;
    if (r < R - 1 && map[r + 1][c] == '.') count++;
    if (c > 0 && map[r][c - 1] == '.') count++;
    if (c < C - 1 && map[r][c + 1] == '.') count++;
    return count == 1;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf(" %s", map[i]);
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '.' && is_dead_end(i, j)) {
                printf("1\n");
                return 0;
            }
        }
    }

    printf("0\n");
    return 0;
}