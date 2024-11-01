#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

char map[MAX_SIZE][MAX_SIZE];
int R, C, N;
int startRow, startCol;

void markPossiblePositions(int row, int col, int direction) {
    switch (direction) {
        case 0: // NORTH
            while (row > 0 && map[row-1][col] == '.') {
                map[row-1][col] = '*';
                row--;
            }
            break;
        case 1: // SOUTH
            while (row < R-1 && map[row+1][col] == '.') {
                map[row+1][col] = '*';
                row++;
            }
            break;
        case 2: // WEST
            while (col > 0 && map[row][col-1] == '.') {
                map[row][col-1] = '*';
                col--;
            }
            break;
        case 3: // EAST
            while (col < C-1 && map[row][col+1] == '.') {
                map[row][col+1] = '*';
                col++;
            }
            break;
    }
}

int main() {
    char direction[10];

    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                startRow = i;
                startCol = j;
            }
        }
    }

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", direction);
        if (strcmp(direction, "NORTH") == 0) {
            markPossiblePositions(startRow, startCol, 0);
        } else if (strcmp(direction, "SOUTH") == 0) {
            markPossiblePositions(startRow, startCol, 1);
        } else if (strcmp(direction, "WEST") == 0) {
            markPossiblePositions(startRow, startCol, 2);
        } else if (strcmp(direction, "EAST") == 0) {
            markPossiblePositions(startRow, startCol, 3);
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] != '*') {
                map[i][j] = '.';
            }
        }
    }

    for (int i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }

    return 0;
}