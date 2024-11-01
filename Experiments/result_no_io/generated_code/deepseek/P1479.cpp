#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

int count_fives(int board[SIZE][SIZE]) {
    int count = 0;
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += board[i][j];
        }
        if (sum == 5) count++;
    }
    // Check columns
    for (int j = 0; j < SIZE; j++) {
        int sum = 0;
        for (int i = 0; i < SIZE; i++) {
            sum += board[i][j];
        }
        if (sum == 5) count++;
    }
    // Check main diagonal
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += board[i][i];
    }
    if (sum == 5) count++;
    // Check anti-diagonal
    sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += board[i][SIZE - 1 - i];
    }
    if (sum == 5) count++;
    return count;
}

void place_pieces(int n, int board[SIZE][SIZE], int row, int col, int *k_values, int *k_count) {
    if (n == 0) {
        int k = count_fives(board);
        bool found = false;
        for (int i = 0; i < *k_count; i++) {
            if (k_values[i] == k) {
                found = true;
                break;
            }
        }
        if (!found) {
            k_values[*k_count] = k;
            (*k_count)++;
        }
        return;
    }
    if (row >= SIZE) return;
    int next_row = row, next_col = col + 1;
    if (next_col >= SIZE) {
        next_row++;
        next_col = 0;
    }
    board[row][col] = 1;
    place_pieces(n - 1, board, next_row, next_col, k_values, k_count);
    board[row][col] = 0;
    place_pieces(n, board, next_row, next_col, k_values, k_count);
}

int main() {
    int n;
    scanf("%d", &n);
    int board[SIZE][SIZE] = {0};
    int k_values[13] = {0};
    int k_count = 0;
    place_pieces(n, board, 0, 0, k_values, &k_count);
    int sum = 0;
    for (int i = 0; i < k_count; i++) {
        sum += k_values[i];
    }
    printf("%d\n", sum);
    return 0;
}