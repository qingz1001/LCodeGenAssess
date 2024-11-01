#include <stdio.h>

long long total = 0;
int solutions[3][13];
int sol_count = 0;

int n;
int path[13];

void backtrack(int row, unsigned int cols, unsigned int diag1, unsigned int diag2) {
    if (row == n) {
        if (sol_count < 3) {
            for(int i = 0; i < n; i++) {
                solutions[sol_count][i] = path[i] + 1;
            }
        }
        sol_count++;
        return;
    }
    for(int col = 0; col < n; col++) {
        unsigned int d1 = row + col;
        unsigned int d2 = n - 1 + col - row;
        if( !(cols & (1 << col)) && !(diag1 & (1 << d1)) && !(diag2 & (1 << d2)) ) {
            path[row] = col;
            backtrack(row + 1, cols | (1 << col), diag1 | (1 << d1), diag2 | (1 << d2));
        }
    }
}

int main(){
    scanf("%d", &n);
    backtrack(0, 0, 0, 0);
    for(int i = 0; i < (sol_count <3 ? sol_count : 3); i++){
        for(int j = 0; j < n; j++){
            printf("%d", solutions[i][j]);
            if(j != n-1) printf(" ");
        }
        printf("\n");
    }
    printf("%d\n", sol_count);
    return 0;
}