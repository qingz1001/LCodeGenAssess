#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

char grid[MAX_N][MAX_M + 1];

int is_valid(int row, int col, char color) {
    if (row > 0 && grid[row - 1][col] == color) return 0;
    if (col > 0 && grid[row][col - 1] == color) return 0;
    return 1;
}

void solve(int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                if (is_valid(i, j, c)) {
                    grid[i][j] = c;
                    break;
                }
            }
        }
        grid[i][M] = '\0';
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    solve(N, M);
    
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i]);
    }
    
    return 0;
}