#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 8

char board[BOARD_SIZE][BOARD_SIZE];
int x, y;
char direction;

void move(int steps) {
    int dx = 0, dy = 0;
    switch (direction) {
        case '^': dy = -1; break;
        case '<': dx = -1; break;
        case '>': dx = 1; break;
        case 'v': dy = 1; break;
    }
    for (int i = 0; i < steps; i++) {
        int nx = x + dx, ny = y + dy;
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
            if (board[nx][ny] != '.') {
                // Push the piece forward
                char temp = board[nx][ny];
                board[nx][ny] = '.';
                board[x][y] = temp;
                x = nx;
                y = ny;
            } else {
                x = nx;
                y = ny;
            }
        } else {
            break;
        }
    }
}

void turn_left() {
    switch (direction) {
        case '^': direction = '<'; break;
        case '<': direction = 'v'; break;
        case 'v': direction = '>'; break;
        case '>': direction = '^'; break;
    }
}

void turn_right() {
    switch (direction) {
        case '^': direction = '>'; break;
        case '<': direction = '^'; break;
        case 'v': direction = '<'; break;
        case '>': direction = 'v'; break;
    }
}

void turn_back() {
    switch (direction) {
        case '^': direction = 'v'; break;
        case '<': direction = '>'; break;
        case 'v': direction = '^'; break;
        case '>': direction = '<'; break;
    }
}

int main() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        scanf("%s", board[i]);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '^' || board[i][j] == '<' || board[i][j] == '>' || board[i][j] == 'v') {
                x = i;
                y = j;
                direction = board[i][j];
                board[i][j] = '.';
            }
        }
    }

    char operation[10];
    while (scanf("%s", operation) != EOF && strcmp(operation, "#") != 0) {
        if (strcmp(operation, "move") == 0) {
            int steps;
            scanf("%d", &steps);
            move(steps);
        } else if (strcmp(operation, "turn left") == 0) {
            turn_left();
        } else if (strcmp(operation, "turn right") == 0) {
            turn_right();
        } else if (strcmp(operation, "turn back") == 0) {
            turn_back();
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%s\n", board[i]);
    }

    return 0;
}