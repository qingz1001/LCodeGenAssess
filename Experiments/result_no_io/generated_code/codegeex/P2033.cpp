#include <stdio.h>
#include <string.h>

char board[8][8];
int x, y, dir;

void move(int n) {
    int nx, ny;
    while (n > 0) {
        nx = x + dx[dir];
        ny = y + dy[dir];
        if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) break;
        if (board[nx][ny] != '.') {
            int nnx = nx + dx[dir];
            int nny = ny + dy[dir];
            if (nnx < 0 || nnx >= 8 || nny < 0 || nny >= 8) break;
            board[nnx][nny] = board[nx][ny];
            board[nx][ny] = '.';
        }
        x = nx;
        y = ny;
        n--;
    }
}

void turn_left() {
    dir = (dir + 3) % 4;
}

void turn_right() {
    dir = (dir + 1) % 4;
}

void turn_back() {
    dir = (dir + 2) % 4;
}

int main() {
    // Initialize board and find initial position and direction
    for (int i = 0; i < 8; i++) {
        scanf("%s", board[i]);
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == '^') {
                x = i;
                y = j;
                dir = 0;
            } else if (board[i][j] == '<') {
                x = i;
                y = j;
                dir = 1;
            } else if (board[i][j] == '>') {
                x = i;
                y = j;
                dir = 2;
            } else if (board[i][j] == 'v') {
                x = i;
                y = j;
                dir = 3;
            }
        }
    }

    // Read and execute commands
    char command[20];
    while (scanf("%s", command) != EOF) {
        if (command[0] == '#') break;
        else if (command[0] == 'm') {
            int n = atoi(command + 5);
            move(n);
        } else if (command[0] == 't' && command[1] == 'u') {
            turn_up();
        } else if (command[0] == 't' && command[1] == 'r') {
            turn_right();
        } else if (command[0] == 't' && command[1] == 'b') {
            turn_back();
        }
    }

    // Print final board state
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == x && j == y) {
                if (dir == 0) printf("^");
                else if (dir == 1) printf("<");
                else if (dir == 2) printf(">");
                else if (dir == 3) printf("v");
            } else {
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}