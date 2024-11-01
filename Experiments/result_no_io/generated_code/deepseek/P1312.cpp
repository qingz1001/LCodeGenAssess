#include <stdio.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 5

int board[ROWS][COLS];
int n;

void print_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void drop_blocks() {
    for (int j = 0; j < COLS; j++) {
        int write_pos = ROWS - 1;
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[write_pos--][j] = board[i][j];
            }
        }
        while (write_pos >= 0) {
            board[write_pos--][j] = 0;
        }
    }
}

int eliminate_blocks() {
    int eliminated = 0;
    int to_eliminate[ROWS][COLS] = {0};

    // Check rows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 2; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                to_eliminate[i][j] = to_eliminate[i][j + 1] = to_eliminate[i][j + 2] = 1;
                eliminated = 1;
            }
        }
    }

    // Check columns
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS - 2; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                to_eliminate[i][j] = to_eliminate[i + 1][j] = to_eliminate[i + 2][j] = 1;
                eliminated = 1;
            }
        }
    }

    // Eliminate marked blocks
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (to_eliminate[i][j]) {
                board[i][j] = 0;
            }
        }
    }

    return eliminated;
}

int is_board_empty() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int steps) {
    if (steps == n) {
        return is_board_empty();
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != 0) {
                if (j < COLS - 1 && board[i][j] != board[i][j + 1]) {
                    // Move right
                    int temp = board[i][j];
                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = temp;

                    drop_blocks();
                    while (eliminate_blocks()) {
                        drop_blocks();
                    }

                    if (solve(steps + 1)) {
                        printf("%d %d 1\n", j, i);
                        return 1;
                    }

                    // Restore board
                    temp = board[i][j];
                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = temp;
                }

                if (j > 0 && board[i][j - 1] == 0) {
                    // Move left
                    int temp = board[i][j];
                    board[i][j] = board[i][j - 1];
                    board[i][j - 1] = temp;

                    drop_blocks();
                    while (eliminate_blocks()) {
                        drop_blocks();
                    }

                    if (solve(steps + 1)) {
                        printf("%d %d -1\n", j, i);
                        return 1;
                    }

                    // Restore board
                    temp = board[i][j];
                    board[i][j] = board[i][j - 1];
                    board[i][j - 1] = temp;
                }
            }
        }
    }

    return 0;
}

int main() {
    scanf("%d", &n);
    for (int j = 0; j < COLS; j++) {
        int i = 0;
        while (1) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) break;
            i++;
        }
    }

    if (!solve(0)) {
        printf("-1\n");
    }

    return 0;
}