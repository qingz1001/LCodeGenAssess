#include <stdio.h>
#include <stdlib.h>

#define N 13

int n, solutions[100][N];
int count = 0;

int is_valid(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (solutions[i][col] == col || abs(solutions[i][col] - col) == row - i) {
            return 0;
        }
    }
    return 1;
}

void solve(int row) {
    if (row == n) {
        if (count < 3) {
            for (int j = 0; j < n; j++) {
                printf("%d ", solutions[count][j]);
            }
            printf("\n");
        }
        count++;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (is_valid(row, col)) {
            solutions[row][col] = col;
            solve(row + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    solve(0);
    printf("%d\n", count);
    return 0;
}