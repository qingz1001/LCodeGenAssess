#include <stdio.h>
#include <string.h>

#define SIZE 8

char board[SIZE][SIZE];
int x, y;
char direction;

void move(int steps) {
    int dx = 0, dy = 0;
    switch (direction) {
        case '^': dx = -1; break;
        case 'v': dx = 1; break;
        case '<': dy = -1; break;
        case '>': dy = 1; break;
    }

    for (int i = 0; i < steps; i++) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) break;

        if (board[nx][ny] != '.') {
            int nnx = nx + dx;
            int nny = ny + dy;
            if (nnx < 0 || nnx >= SIZE || nny < 0 || nny >= SIZE) break;
            board[nnx][nny] = board[nx][ny];
        }

        board[x][y] = '.';
        x = nx;
        y = ny;
        board[x][y] = direction;
    }
}

void turn(char dir) {
    switch (dir) {
        case 'l':
            switch (direction) {
                case '^': direction = '<'; break;
                case 'v': direction = '>'; break;
                case '<': direction = 'v'; break;
                case '>': direction = '^'; break;
            }
            break;
        case 'r':
            switch (direction) {
                case '^': direction = '>'; break;
                case 'v': direction = '<'; break;
                case '<': direction = '^'; break;
                case '>': direction = 'v'; break;
            }
            break;
        case 'b':
            switch (direction) {
                case '^': direction = 'v'; break;
                case 'v': direction = '^'; break;
                case '<': direction = '>'; break;
                case '>': direction = '<'; break;
            }
            break;
    }
    board[x][y] = direction;
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf(" %c", &board[i][j]);
            if (board[i][j] == '^' || board[i][j] == 'v' || board[i][j] == '<' || board[i][j] == '>') {
                x = i;
                y = j;
                direction = board[i][j];
            }
        }
    }

    char command[10];
    while (scanf("%s", command) == 1 && command[0] != '#') {
        if (command[0] == 'm') {
            int steps;
            scanf("%d", &steps);
            move(steps);
        } else if (command[0] == 't') {
            char dir;
            scanf(" %c", &dir);
            turn(dir);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}