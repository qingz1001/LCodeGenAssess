#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 8

char board[BOARD_SIZE][BOARD_SIZE];
int playerX, playerY;
char playerDirection;

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        scanf("%s", board[i]);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '^' || board[i][j] == '<' || board[i][j] == '>' || board[i][j] == 'v') {
                playerX = j;
                playerY = i;
                playerDirection = board[i][j];
                board[i][j] = '.';
            }
        }
    }
}

void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == playerY && j == playerX) {
                printf("%c", playerDirection);
            } else {
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }
}

void move(int steps) {
    int dx = 0, dy = 0;
    switch (playerDirection) {
        case '^': dy = -1; break;
        case 'v': dy = 1; break;
        case '<': dx = -1; break;
        case '>': dx = 1; break;
    }

    for (int i = 0; i < steps; i++) {
        int newX = playerX + dx;
        int newY = playerY + dy;

        if (newX < 0 || newX >= BOARD_SIZE || newY < 0 || newY >= BOARD_SIZE) {
            break;
        }

        if (board[newY][newX] != '.') {
            int nextX = newX + dx;
            int nextY = newY + dy;
            if (nextX >= 0 && nextX < BOARD_SIZE && nextY >= 0 && nextY < BOARD_SIZE && board[nextY][nextX] == '.') {
                board[nextY][nextX] = board[newY][newX];
                board[newY][newX] = '.';
            } else {
                break;
            }
        }

        playerX = newX;
        playerY = newY;
    }
}

void turn(const char* direction) {
    if (strcmp(direction, "left") == 0) {
        switch (playerDirection) {
            case '^': playerDirection = '<'; break;
            case '<': playerDirection = 'v'; break;
            case 'v': playerDirection = '>'; break;
            case '>': playerDirection = '^'; break;
        }
    } else if (strcmp(direction, "right") == 0) {
        switch (playerDirection) {
            case '^': playerDirection = '>'; break;
            case '>': playerDirection = 'v'; break;
            case 'v': playerDirection = '<'; break;
            case '<': playerDirection = '^'; break;
        }
    } else if (strcmp(direction, "back") == 0) {
        switch (playerDirection) {
            case '^': playerDirection = 'v'; break;
            case 'v': playerDirection = '^'; break;
            case '<': playerDirection = '>'; break;
            case '>': playerDirection = '<'; break;
        }
    }
}

int main() {
    initializeBoard();

    char operation[20];
    while (1) {
        scanf("%s", operation);
        if (operation[0] == '#') break;

        if (strcmp(operation, "move") == 0) {
            int steps;
            scanf("%d", &steps);
            move(steps);
        } else if (strcmp(operation, "turn") == 0) {
            char direction[10];
            scanf("%s", direction);
            turn(direction);
        }
    }

    printBoard();
    return 0;
}