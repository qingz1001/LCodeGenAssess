#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
#define TARGET_SUM 34

int grid[SIZE][SIZE];
int used[17];
int solutions[10000][SIZE][SIZE];
int sol_count = 0;
int fixed_i, fixed_j;

void print_grid(int g[SIZE][SIZE]) {
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int check_constraints(int row, int col) {
    // Check row
    int sum = 0;
    int filled = 1;
    for(int j=0;j<SIZE;j++) {
        if(grid[row][j] == 0) { filled = 0; break;}
        sum += grid[row][j];
    }
    if(filled && sum != TARGET_SUM) return 0;
    // Check column
    sum = 0;
    filled = 1;
    for(int i=0;i<SIZE;i++) {
        if(grid[i][col] == 0) { filled = 0; break;}
        sum += grid[i][col];
    }
    if(filled && sum != TARGET_SUM) return 0;
    // Check diagonals
    if(row == col) {
        sum = 0;
        filled = 1;
        for(int i=0;i<SIZE;i++) {
            if(grid[i][i]==0){filled=0; break;}
            sum += grid[i][i];
        }
        if(filled && sum != TARGET_SUM) return 0;
    }
    if(row + col == SIZE -1) {
        sum = 0;
        filled = 1;
        for(int i=0;i<SIZE;i++) {
            if(grid[i][SIZE-1-i]==0){filled=0; break;}
            sum += grid[i][SIZE-1-i];
        }
        if(filled && sum != TARGET_SUM) return 0;
    }
    // Check 2x2 squares
    if(row > 0 && col > 0) {
        sum = grid[row][col] + grid[row-1][col] + grid[row][col-1] + grid[row-1][col-1];
        if(grid[row][col] && grid[row-1][col] && grid[row][col-1] && grid[row-1][col-1]){
            if(sum != TARGET_SUM) return 0;
        }
    }
    // Check corners
    if(row == SIZE-1 && col == SIZE-1) {
        sum = grid[0][0] + grid[0][SIZE-1] + grid[SIZE-1][0] + grid[SIZE-1][SIZE-1];
        if(grid[0][0] && grid[0][SIZE-1] && grid[SIZE-1][0] && grid[SIZE-1][SIZE-1]){
            if(sum != TARGET_SUM) return 0;
        }
    }
    // Check center 2x2
    if(row >=1 && row <=2 && col >=1 && col <=2){
        sum = grid[1][1] + grid[1][2] + grid[2][1] + grid[2][2];
        if(grid[1][1] && grid[1][2] && grid[2][1] && grid[2][2]){
            if(sum != TARGET_SUM) return 0;
        }
    }
    return 1;
}

void backtrack(int pos) {
    if(pos == SIZE*SIZE){
        // Found a solution
        print_grid(grid);
        sol_count++;
        return;
    }
    int i = pos / SIZE;
    int j = pos % SIZE;
    if(grid[i][j] != 0){
        backtrack(pos+1);
        return;
    }
    for(int num=1; num<=16; num++) {
        if(!used[num]){
            grid[i][j] = num;
            used[num] = 1;
            if(check_constraints(i, j)){
                backtrack(pos+1);
            }
            grid[i][j] = 0;
            used[num] = 0;
        }
    }
}

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    fixed_i = a-1;
    fixed_j = b-1;
    memset(grid, 0, sizeof(grid));
    memset(used, 0, sizeof(used));
    grid[fixed_i][fixed_j] = 1;
    used[1] = 1;
    backtrack(0);
    return 0;
}