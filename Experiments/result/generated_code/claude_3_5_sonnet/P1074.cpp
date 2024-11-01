#include <stdio.h>
#include <stdbool.h>

#define N 9

int grid[N][N];
int score[N][N] = {
    {6,6,6,7,7,7,6,6,6},
    {6,7,7,8,8,8,7,7,6},
    {6,7,8,9,9,9,8,7,6},
    {7,8,9,10,10,10,9,8,7},
    {7,8,9,10,10,10,9,8,7},
    {7,8,9,10,10,10,9,8,7},
    {6,7,8,9,9,9,8,7,6},
    {6,7,7,8,8,8,7,7,6},
    {6,6,6,7,7,7,6,6,6}
};

int max_score = -1;

bool is_valid(int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;
    
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;
    
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    
    return true;
}

void calculate_score() {
    int total = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            total += grid[i][j] * score[i][j];
    
    if (total > max_score)
        max_score = total;
}

bool solve(int row, int col) {
    if (row == N - 1 && col == N)
        return true;
    
    if (col == N) {
        row++;
        col = 0;
    }
    
    if (grid[row][col] > 0)
        return solve(row, col + 1);
    
    for (int num = 1; num <= N; num++) {
        if (is_valid(row, col, num)) {
            grid[row][col] = num;
            
            if (solve(row, col + 1))
                calculate_score();
            
            grid[row][col] = 0;
        }
    }
    
    return false;
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &grid[i][j]);
    
    solve(0, 0);
    
    printf("%d\n", max_score);
    
    return 0;
}