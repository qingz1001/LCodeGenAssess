#include <stdio.h>
#include <string.h>

#define SIZE 8

char board[SIZE][SIZE];
int x, y, direction;

// 方向: 0-上, 1-右, 2-下, 3-左
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void move(int steps) {
    while (steps--) {
        int nx = x + dx[direction], ny = y + dy[direction];
        if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) break;
        
        if (board[nx][ny] != '.') {
            int nnx = nx + dx[direction], nny = ny + dy[direction];
            if (nnx < 0 || nnx >= SIZE || nny < 0 || nny >= SIZE) break;
            board[nnx][nny] = board[nx][ny];
        }
        
        board[nx][ny] = "^>v<"[direction];
        board[x][y] = '.';
        x = nx;
        y = ny;
    }
}

void turn(char* command) {
    if (strcmp(command, "left") == 0) direction = (direction + 3) % 4;
    else if (strcmp(command, "right") == 0) direction = (direction + 1) % 4;
    else if (strcmp(command, "back") == 0) direction = (direction + 2) % 4;
    board[x][y] = "^>v<"[direction];
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf(" %c", &board[i][j]);
            if (board[i][j] == '^') { x = i; y = j; direction = 0; }
            if (board[i][j] == '>') { x = i; y = j; direction = 1; }
            if (board[i][j] == 'v') { x = i; y = j; direction = 2; }
            if (board[i][j] == '<') { x = i; y = j; direction = 3; }
        }
    }

    char command[10];
    int steps;
    while (1) {
        scanf("%s", command);
        if (command[0] == '#') break;
        if (strcmp(command, "move") == 0) {
            scanf("%d", &steps);
            move(steps);
        } else {
            turn(command + 5);  // Skip "turn "
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