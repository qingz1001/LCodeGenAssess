#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 8

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    int x, y;
    int direction; // 0: up, 1: right, 2: down, 3: left
} Chessboard;

void move(Chessboard *cb, int steps) {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 0; i < steps; i++) {
        int nx = cb->x + dx[cb->direction];
        int ny = cb->y + dy[cb->direction];
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
            if (cb->board[nx][ny] != '.') {
                cb->board[cb->x][cb->y] = '.';
                cb->x = nx;
                cb->y = ny;
                cb->board[cb->x][cb->y] = '^';
            } else {
                cb->x = nx;
                cb->y = ny;
            }
        } else {
            break;
        }
    }
}

void turn_left(Chessboard *cb) {
    cb->direction = (cb->direction + 3) % 4;
}

void turn_right(Chessboard *cb) {
    cb->direction = (cb->direction + 1) % 4;
}

void turn_back(Chessboard *cb) {
    cb->direction = (cb->direction + 2) % 4;
}

void process_operations(Chessboard *cb, const char *operations) {
    int len = strlen(operations);
    for (int i = 0; i < len; i++) {
        if (operations[i] == 'm') {
            int j = i + 1;
            while (j < len && operations[j] >= '0' && operations[j] <= '9') {
                j++;
            }
            int steps = atoi(&operations[i + 1]);
            move(cb, steps);
            i = j - 1;
        } else if (operations[i] == 'l') {
            turn_left(cb);
        } else if (operations[i] == 'r') {
            turn_right(cb);
        } else if (operations[i] == 'b') {
            turn_back(cb);
        }
    }
}

int main() {
    Chessboard cb;
    for (int i = 0; i < BOARD_SIZE; i++) {
        scanf("%s", cb.board[i]);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (cb.board[i][j] == '^' || cb.board[i][j] == '<' || cb.board[i][j] == '>' || cb.board[i][j] == 'v') {
                cb.x = i;
                cb.y = j;
                switch (cb.board[i][j]) {
                    case '^': cb.direction = 0; break;
                    case '>': cb.direction = 1; break;
                    case 'v': cb.direction = 2; break;
                    case '<': cb.direction = 3; break;
                }
                cb.board[i][j] = '.';
            }
        }
    }

    char operations[1001];
    scanf("%s", operations);

    process_operations(&cb, operations);

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%s\n", cb.board[i]);
    }

    return 0;
}