#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define TARGET 34

int grid[N][N];
int used[17];
int fixed_i, fixed_j;
int solutions[100000][N][N];
int sol_count = 0;

// Conditions to check after placing a number
int check_conditions(int row, int col) {
    // Check rows
    if (row == N-1) {
        int sum = 0;
        for(int j=0;j<N;j++) sum += grid[row][j];
        if(sum != TARGET) return 0;
    }
    // Check columns
    if (col == N-1) {
        int sum = 0;
        for(int i=0;i<N;i++) sum += grid[i][col];
        if(sum != TARGET) return 0;
    }
    // Check 2x2 corners
    if (row >=1 && col >=1) {
        if (row ==1 && col ==1) {
            int sum = grid[0][0] + grid[0][1] + grid[1][0] + grid[1][1];
            if(sum != TARGET) return 0;
        }
        if (row ==1 && col ==2) {
            int sum = grid[0][3] + grid[0][2] + grid[1][3] + grid[1][2];
            if(sum != TARGET) return 0;
        }
        if (row ==2 && col ==1) {
            int sum = grid[3][0] + grid[3][1] + grid[2][0] + grid[2][1];
            if(sum != TARGET) return 0;
        }
        if (row ==2 && col ==2) {
            int sum = grid[3][3] + grid[3][2] + grid[2][3] + grid[2][2];
            if(sum != TARGET) return 0;
        }
    }
    // Check middle 2x2
    if (row ==3 && col ==3) {
        int sum = grid[1][1] + grid[1][2] + grid[2][1] + grid[2][2];
        if(sum != TARGET) return 0;
    }
    // Check diagonals
    if (row ==3 && col ==3) {
        int sum1 = grid[0][0] + grid[1][1] + grid[2][2] + grid[3][3];
        if(sum1 != TARGET) return 0;
        int sum2 = grid[0][3] + grid[1][2] + grid[2][1] + grid[3][0];
        if(sum2 != TARGET) return 0;
    }
    return 1;
}

int compare_solutions(const void *a, const void *b) {
    int (*solA)[N][N] = a;
    int (*solB)[N][N] = b;
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if((*solA)[i][j] < (*solB)[i][j]) return -1;
            if((*solA)[i][j] > (*solB)[i][j]) return 1;
        }
    }
    return 0;
}

void backtrack(int pos) {
    if(sol_count >= 100000) return;
    if(pos == N*N) {
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                solutions[sol_count][i][j] = grid[i][j];
            }
        }
        sol_count++;
        return;
    }
    int i = pos / N;
    int j = pos % N;
    if(i == fixed_i && j == fixed_j) {
        backtrack(pos+1);
        return;
    }
    for(int num=1; num<=16; num++) {
        if(!used[num]) {
            grid[i][j] = num;
            used[num] = 1;
            if(check_conditions(i, j)) {
                backtrack(pos+1);
            }
            used[num] = 0;
        }
    }
}

int main(){
    int i, j;
    scanf("%d %d", &i, &j);
    fixed_i = i-1;
    fixed_j = j-1;
    memset(grid, 0, sizeof(grid));
    memset(used, 0, sizeof(used));
    grid[fixed_i][fixed_j] = 1;
    used[1] = 1;
    backtrack(0);
    qsort(solutions, sol_count, sizeof(solutions[0]), compare_solutions);
    for(int s=0;s<sol_count;s++) {
        for(int r=0;r<N;r++) {
            for(int c=0;c<N;c++) {
                printf("%d", solutions[s][r][c]);
                if(c < N-1) printf(" ");
            }
            printf("\n");
        }
        if(s < sol_count-1) printf("\n");
    }
    return 0;
}