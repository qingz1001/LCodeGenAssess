#include <stdio.h>
#include <stdlib.h>

#define MAX_SOLUTIONS 3

int n;
int pos[20];
int col_used[20];
int diag1_used[40];
int diag2_used[40];
int solutions[MAX_SOLUTIONS][20];
int sol_count = 0;
long long total = 0;

void backtrack(int row) {
    if (row == n) {
        if (sol_count < MAX_SOLUTIONS) {
            for(int i = 0; i < n; i++) {
                solutions[sol_count][i] = pos[i] + 1;
            }
            sol_count++;
        }
        total++;
        return;
    }
    for(int c = 0; c < n; c++) {
        if(!col_used[c] && !diag1_used[row + c] && !diag2_used[row - c + n -1]) {
            pos[row] = c;
            col_used[c] = diag1_used[row + c] = diag2_used[row - c + n -1] = 1;
            backtrack(row + 1);
            col_used[c] = diag1_used[row + c] = diag2_used[row - c + n -1] = 0;
        }
    }
}

int main(){
    scanf("%d", &n);
    backtrack(0);
    for(int i = 0; i < sol_count; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d%c", solutions[i][j], j < n-1 ? ' ' : '\n');
        }
    }
    printf("%lld\n", total);
    return 0;
}