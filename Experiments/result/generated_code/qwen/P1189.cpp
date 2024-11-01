#include <stdio.h>
#include <stdlib.h>

#define MAX_R 50
#define MAX_C 50

void moveCar(char map[MAX_R][MAX_C], int *r, int *c, char direction) {
    switch (direction) {
        case 'N':
            (*r)--;
            break;
        case 'S':
            (*r)++;
            break;
        case 'W':
            (*c)--;
            break;
        case 'E':
            (*c)++;
            break;
    }
}

int isValidMove(char map[MAX_R][MAX_C], int r, int c) {
    return r >= 0 && r < MAX_R && c >= 0 && c < MAX_C && map[r][c] != 'X';
}

void markPossiblePositions(char map[MAX_R][MAX_C], int R, int C) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                map[i][j] = '!';
            }
        }
    }
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    char map[MAX_R][MAX_C];
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }

    int startR, startC;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '*') {
                startR = i;
                startC = j;
                map[i][j] = '!';
                break;
            }
        }
    }

    int N;
    scanf("%d", &N);
    char directions[N];
    for (int i = 0; i < N; i++) {
        scanf("%s", directions + i);
    }

    int currentR = startR, currentC = startC;
    for (int i = 0; i < N; i++) {
        moveCar(map, &currentR, &currentC, directions[i][0]);
        while (isValidMove(map, currentR, currentC)) {
            map[currentR][currentC] = '!';
            moveCar(map, &currentR, &currentC, directions[i][0]);
        }
        moveCar(map, &currentR, &currentC, directions[i][0]);
    }

    markPossiblePositions(map, R, C);

    for (int i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }

    return 0;
}