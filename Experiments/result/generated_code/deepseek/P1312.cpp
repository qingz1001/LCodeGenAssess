#include <stdio.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 5

int board[ROWS][COLS];
int n;

typedef struct {
    int x, y, g;
} Move;

Move moves[5];

void print_moves() {
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", moves[i].x, moves[i].y, moves[i].g);
    }
}

void drop_blocks() {
    for (int col = 0; col < COLS; col++) {
        int write_pos = ROWS - 1;
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] != 0) {
                board[write_pos--][col] = board[row][col];
            }
        }
        while (write_pos >= 0) {
            board[write_pos--][col] = 0;
        }
    }
}

int is_valid_move(int x, int y, int g) {
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) return 0;
    if (g == 1 && y == COLS - 1) return 0;
    if (g == -1 && y == 0) return 0;
    if (g == 1 && board[x][y] == board[x][y + 1]) return 0;
    if (g == -1 && board[x][y] == board[x][y - 1]) return 0;
    return 1;
}

void swap_blocks(int x, int y, int g) {
    int temp = board[x][y];
    board[x][y] = board[x][y + g];
    board[x][y + g] = temp;
}

int check_and_remove_blocks() {
    int to_remove[ROWS][COLS] = {0};
    int removed = 0;

    // Check horizontally
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS - 2; col++) {
            if (board[row][col] != 0 && board[row][col] == board[row][col + 1] && board[row][col] == board[row][col + 2]) {
                to_remove[row][col] = to_remove[row][col + 1] = to_remove[row][col + 2] = 1;
                removed = 1;
            }
        }
    }

    // Check vertically
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS - 2; row++) {
            if (board[row][col] != 0 && board[row][col] == board[row + 1][col] && board[row][col] == board[row + 2][col]) {
                to_remove[row][col] = to_remove[row + 1][col] = to_remove[row + 2][col] = 1;
                removed = 1;
            }
        }
    }

    // Remove marked blocks
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (to_remove[row][col]) {
                board[row][col] = 0;
            }
        }
    }

    return removed;
}

int is_board_empty() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

int solve(int depth) {
    if (depth == n) {
        return is_board_empty();
    }

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (board[row][col] != 0) {
                for (int g = -1; g <= 1; g += 2) {
                    if (is_valid_move(row, col, g)) {
                        swap_blocks(row, col, g);
                        drop_blocks();
                        while (check_and_remove_blocks()) {
                            drop_blocks();
                        }

                        moves[depth].x = row;
                        moves[depth].y = col;
                        moves[depth].g = g;

                        if (solve(depth + 1)) {
                            return 1;
                        }

                        swap_blocks(row, col, g);
                        drop_blocks();
                        while (check_and_remove_blocks()) {
                            drop_blocks();
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int main() {
    scanf("%d", &n);

    for (int col = 0; col < COLS; col++) {
        int row = 0;
        while (1) {
            scanf("%d", &board[row][col]);
            if (board[row][col] == 0) break;
            row++;
        }
    }

    if (solve(0)) {
        print_moves();
    } else {
        printf("-1\n");
    }

    return 0;
}