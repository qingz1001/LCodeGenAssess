#include <stdio.h>
#include <string.h>

char board[8][8];
int x, y, dir; // dir: 0=up, 1=left, 2=right, 3=down

void move(int n) {
    int nx = x, ny = y;
    while (n > 0) {
        if (dir == 0) {
            if (nx == 0) break;
            nx--;
        } else if (dir == 1) {
            if (ny == 0) break;
            ny--;
        } else if (dir == 2) {
            if (ny == 7) break;
            ny++;
        } else if (dir == 3) {
            if (nx == 7) break;
            nx++;
        }
        if (board[nx][ny] != '.') {
            int nnx = nx, nny = ny;
            while (board[nnx][nny] != '.') {
                if (dir == 0) nnx++;
                else if (dir == 1) nny++;
                else if (dir == 2) nny--;
                else if (dir == 3) nnx--;
            }
            char temp = board[nnx][nny];
            board[nnx][nny] = board[nx][ny];
            board[nx][ny] = temp;
        } else {
            board[nx][ny] = board[x][y];
            board[x][y] = '.';
        }
        n--;
    }
}

void turn_left() {
    dir = (dir + 1) % 4;
}

void turn_right() {
    dir = (dir + 3) % 4;
}

void turn_back() {
    dir = (dir + 2) % 4;
}

int main() {
    // Read the initial board state
    for (int i = 0; i < 8; i++) {
        scanf("%s", board[i]);
    }
    // Determine initial position and direction
    for (int i = 0; i < 8; i++) {
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
    // Process commands
    char command[10];
    while (1) {
        scanf("%s", command);
        if (command[0] == '#') break;
        if (strcmp(command, "move") == 0) {
            int n;
            scanf("%d", &n);
            move(n);
        } else if (strcmp(command, "turn left") == 0) {
            turn_left();
        } else if (strcmp(command, "turn right") == 0) {
            turn_right();
        } else if (strcmp(command, "turn back") == 0) {
            turn_back();
        }
    }
    // Print the final board state
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