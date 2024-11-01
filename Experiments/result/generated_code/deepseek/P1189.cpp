#include <stdio.h>
#include <string.h>

#define MAX 50

char map[MAX][MAX];
int R, C;

void move(int *x, int *y, char direction) {
    switch (direction) {
        case 'N':
            (*x)--;
            break;
        case 'S':
            (*x)++;
            break;
        case 'W':
            (*y)--;
            break;
        case 'E':
            (*y)++;
            break;
    }
}

void simulate(int start_x, int start_y, char directions[], int N) {
    int x = start_x, y = start_y;
    map[x][y] = '*';

    for (int i = 0; i < N; i++) {
        char direction = directions[i];
        int new_x = x, new_y = y;
        move(&new_x, &new_y, direction);

        while (new_x >= 0 && new_x < R && new_y >= 0 && new_y < C && map[new_x][new_y] != 'X') {
            map[new_x][new_y] = '*';
            x = new_x;
            y = new_y;
            move(&new_x, &new_y, direction);
        }
    }
}

int main() {
    scanf("%d %d", &R, &C);
    int start_x = -1, start_y = -1;

    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
        if (start_x == -1) {
            for (int j = 0; j < C; j++) {
                if (map[i][j] == '*') {
                    start_x = i;
                    start_y = j;
                    map[i][j] = '.';
                    break;
                }
            }
        }
    }

    int N;
    scanf("%d", &N);
    char directions[N];
    for (int i = 0; i < N; i++) {
        char dir[6];
        scanf("%s", dir);
        if (strcmp(dir, "NORTH") == 0) directions[i] = 'N';
        else if (strcmp(dir, "SOUTH") == 0) directions[i] = 'S';
        else if (strcmp(dir, "WEST") == 0) directions[i] = 'W';
        else if (strcmp(dir, "EAST") == 0) directions[i] = 'E';
    }

    simulate(start_x, start_y, directions, N);

    for (int i = 0; i < R; i++) {
        printf("%s\n", map[i]);
    }

    return 0;
}