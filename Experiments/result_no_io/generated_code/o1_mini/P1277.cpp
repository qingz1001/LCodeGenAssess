#include <stdio.h>
#include <stdlib.h>

int M[4][4];
int row_sum[4], col_sum[4];
int diag1_sum, diag2_sum;
int given[4][3];
int solution_found = 0;

typedef struct {
    int i;
    int j;
} Cell;

Cell cells_to_fill[16];
int num_cells_to_fill = 0;

void print_matrix() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            printf("%d", M[i][j]);
            if(j < 3) printf(" ");
        }
        printf("\n");
    }
}

void backtrack(int idx) {
    if(solution_found) return;
    if(idx == num_cells_to_fill) {
        // Check if all sums are zero
        for(int i=0;i<4;i++) if(row_sum[i]!=0) return;
        for(int i=0;i<4;i++) if(col_sum[i]!=0) return;
        if(diag1_sum !=0 || diag2_sum !=0) return;
        // Print the solution
        print_matrix();
        solution_found = 1;
        return;
    }
    int i = cells_to_fill[idx].i;
    int j = cells_to_fill[idx].j;
    int max_val = row_sum[i] < col_sum[j] ? row_sum[i] : col_sum[j];
    if(i == j && diag1_sum < max_val) max_val = diag1_sum;
    if(i + j ==3 && diag2_sum < max_val) max_val = diag2_sum;
    for(int val=1; val<=max_val; val++) {
        // Assign val to M[i][j]
        M[i][j] = val;
        row_sum[i] -= val;
        col_sum[j] -= val;
        int diag1 = 0, diag2 = 0;
        if(i == j) {
            diag1_sum -= val;
            diag1 = 1;
        }
        if(i + j ==3) {
            diag2_sum -= val;
            diag2 = 1;
        }
        // Check if any sum is negative
        if(row_sum[i] >=0 && col_sum[j] >=0 && diag1_sum >=0 && diag2_sum >=0) {
            backtrack(idx +1);
        }
        // Backtrack
        M[i][j] = -1;
        row_sum[i] += val;
        col_sum[j] += val;
        if(diag1) {
            diag1_sum += val;
        }
        if(diag2) {
            diag2_sum += val;
        }
        if(solution_found) return;
    }
}

int main(){
    for(int i=0;i<4;i++) scanf("%d", &row_sum[i]);
    for(int i=0;i<4;i++) scanf("%d", &col_sum[i]);
    scanf("%d %d", &diag1_sum, &diag2_sum);
    for(int i=0;i<4;i++) {
        int x, y, val;
        scanf("%d %d %d", &x, &y, &val);
        M[x][y] = val;
        row_sum[x] -= val;
        col_sum[y] -= val;
        if(x == y) diag1_sum -= val;
        if(x + y ==3) diag2_sum -= val;
    }
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(M[i][j] == -1) {
                cells_to_fill[num_cells_to_fill].i = i;
                cells_to_fill[num_cells_to_fill].j = j;
                num_cells_to_fill++;
            }
        }
    }
    backtrack(0);
    return 0;
}