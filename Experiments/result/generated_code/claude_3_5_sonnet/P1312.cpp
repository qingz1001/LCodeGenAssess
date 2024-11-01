#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STEPS 5
#define ROWS 7
#define COLS 5

int board[ROWS][COLS];
int n;
int steps[MAX_STEPS][3];
int step_count = 0;

bool is_valid(int x, int y) {
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}

void fall() {
    for (int x = 0; x < COLS; x++) {
        int bottom = 0;
        for (int y = 0; y < ROWS; y++) {
            if (board[y][x] != 0) {
                board[bottom++][x] = board[y][x];
            }
        }
        while (bottom < ROWS) {
            board[bottom++][x] = 0;
        }
    }
}

bool remove_blocks() {
    bool removed = false;
    int temp[ROWS][COLS];
    memcpy(temp, board, sizeof(board));

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (board[y][x] == 0) continue;

            // Check horizontal
            if (x < COLS - 2 && board[y][x] == board[y][x+1] && board[y][x] == board[y][x+2]) {
                temp[y][x] = temp[y][x+1] = temp[y][x+2] = 0;
                removed = true;
            }

            // Check vertical
            if (y < ROWS - 2 && board[y][x] == board[y+1][x] && board[y][x] == board[y+2][x]) {
                temp[y][x] = temp[y+1][x] = temp[y+2][x] = 0;
                removed = true;
            }
        }
    }

    memcpy(board, temp, sizeof(board));
    return removed;
}

bool dfs(int depth) {
    if (depth == n) {
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++) {
                if (board[y][x] != 0) return false;
            }
        }
        return true;
    }

    int original[ROWS][COLS];
    memcpy(original, board, sizeof(board));

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (board[y][x] == 0) continue;

            // Move right
            if (is_valid(x+1, y)) {
                int temp = board[y][x];
                board[y][x] = board[y][x+1];
                board[y][x+1] = temp;

                fall();
                while (remove_blocks()) fall();

                steps[depth][0] = x;
                steps[depth][1] = y;
                steps[depth][2] = 1;

                if (dfs(depth + 1)) return true;

                memcpy(board, original, sizeof(board));
            }

            // Move left
            if (is_valid(x-1, y)) {
                int temp = board[y][x];
                board[y][x] = board[y][x-1];
                board[y][x-1] = temp;

                fall();
                while (remove_blocks()) fall();

                steps[depth][0] = x;
                steps[depth][1] = y;
                steps[depth][2] = -1;

                if (dfs(depth + 1)) return true;

                memcpy(board, original, sizeof(board));
            }
        }
    }

    return false;
}

int main() {
    scanf("%d", &n);

    for (int x = 0; x < COLS; x++) {
        int y = 0;
        while (1) {
            int color;
            scanf("%d", &color);
            if (color == 0) break;
            board[y++][x] = color;
        }
    }

    if (dfs(0)) {
        for (int i = 0; i < n; i++) {
            printf("%d %d %d\n", steps[i][0], steps[i][1], steps[i][2]);
        }
    } else {
        printf("-1\n");
    }

    return 0;
}