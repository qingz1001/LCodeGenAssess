#include <stdio.h>
#include <stdbool.h>

#define MAX_R 10
#define MAX_C 10

bool isDeadEnd(char map[MAX_R][MAX_C], int r, int c, int R, int C) {
    int count = 0;
    if (r > 0 && map[r - 1][c] == '.') count++;
    if (r < R - 1 && map[r + 1][c] == '.') count++;
    if (c > 0 && map[r][c - 1] == '.') count++;
    if (c < C - 1 && map[r][c + 1] == '.') count++;
    return count == 1;
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    char map[MAX_R][MAX_C];
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf(" %c", &map[i][j]);
        }
    }

    bool hasDeadEnd = false;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '.' && isDeadEnd(map, i, j, R, C)) {
                hasDeadEnd = true;
                break;
            }
        }
        if (hasDeadEnd) break;
    }

    printf("%d\n", hasDeadEnd ? 1 : 0);

    return 0;
}