#include <stdio.h>
#include <string.h>

#define MAX 50

char map[MAX][MAX];
int R, C, N;
char directions[1000][10];

void mark_possible_positions(int x, int y) {
    int i;
    for (i = 0; i < R; i++) {
        int j;
        for (j = 0; j < C; j++) {
            if (map[i][j] == '.') {
                map[i][j] = '*';
            }
        }
    }
    map[x][y] = '*';
}

void process_direction(char* direction, int x, int y) {
    if (strcmp(direction, "NORTH") == 0) {
        while (x > 0 && map[x - 1][y] == '.') {
            x--;
        }
    } else if (strcmp(direction, "SOUTH") == 0) {
        while (x < R - 1 && map[x + 1][y] == '.') {
            x++;
        }
    } else if (strcmp(direction, "WEST") == 0) {
        while (y > 0 && map[x][y - 1] == '.') {
            y--;
        }
    } else if (strcmp(direction, "EAST") == 0) {
        while (y < C - 1 && map[x][y + 1] == '.') {
            y++;
        }
    }
    mark_possible_positions(x, y);
}

int main() {
    scanf("%d %d", &R, &C);
    int i, j;
    for (i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                map[i][j] = '.';
                process_direction("NORTH", i, j);
                process_direction("SOUTH", i, j);
                process_direction("WEST", i, j);
                process_direction("EAST", i, j);
                break;
            }
        }
        if (i < R - 1) {
            break;
        }
    }
    for (i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }
    return 0;
}