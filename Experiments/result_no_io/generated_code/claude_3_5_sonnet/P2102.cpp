#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

char grid[MAX_N][MAX_M + 1];
int N, M;

int is_valid(int row, int col) {
    if (row > 0 && grid[row][col] == grid[row-1][col]) return 0;
    if (col > 0 && grid[row][col] == grid[row][col-1]) return 0;
    return 1;
}

int solve(int row, int col) {
    if (col == M) {
        col = 0;
        row++;
    }
    if (row == N) return 1;

    for (char c = 'A'; c <= 'Z'; c++) {
        grid[row][col] = c;
        if (is_valid(row, col) && solve(row, col + 1))
            return 1;
    }

    return 0;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        grid[i][M] = '\0';
    }

    solve(0, 0);

    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}