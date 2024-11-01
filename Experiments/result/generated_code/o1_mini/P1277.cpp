#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i;
    int j;
} Cell;

int row_sums[4], col_sums[4];
int main_diag_sum, anti_diag_sum;
int M[4][4];
int row_left[4], col_left_left[4];
int main_diag_left, anti_diag_left;
Cell rem[12];
int rem_cnt = 0;
int found = 0;

void print_solution() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            printf("%d", M[i][j]);
            if(j<3) printf(" ");
        }
        printf("\n");
    }
    exit(0);
}

void backtrack(int idx) {
    if(found) return;
    if(idx == rem_cnt) {
        if(main_diag_left ==0 && anti_diag_left ==0) {
            print_solution();
        }
        return;
    }
    int i = rem[idx].i;
    int j = rem[idx].j;
    int max_val = row_left[i] < col_left_left[j] ? row_left[i] : col_left_left[j];
    if(i == j) {
        if(main_diag_left < max_val) max_val = main_diag_left;
    }
    if(i + j == 3) {
        if(anti_diag_left < max_val) max_val = anti_diag_left;
    }
    for(int val=1; val<=max_val; val++) {
        // Check if assigning val is possible
        int new_row = row_left[i] - val;
        int new_col = col_left_left[j] - val;
        int new_main_diag = main_diag_left;
        int new_anti_diag = anti_diag_left;
        if(i == j) new_main_diag -= val;
        if(i + j ==3 ) new_anti_diag -= val;
        // Check if remaining cells can satisfy at least 1
        int possible = 1;
        // Count remaining cells in row i and column j
        int rem_row =0, rem_col=0;
        int rem_main_diag = (i == j) ? 1 : 0;
        int rem_anti_diag = (i + j ==3) ? 1 : 0;
        for(int k=idx+1; k<rem_cnt; k++) {
            if(rem[k].i == i) rem_row++;
            if(rem[k].j == j) rem_col++;
            if(rem[k].i == rem[k].j) rem_main_diag++;
            if(rem[k].i + rem[k].j ==3) rem_anti_diag++;
        }
        if(new_row < rem_row || new_col < rem_col) {
            possible =0;
        }
        if((i == j) && (new_main_diag < rem_main_diag)) possible =0;
        if((i + j ==3) && (new_anti_diag < rem_anti_diag)) possible =0;
        if(new_row <0 || new_col <0) possible =0;
        if((i == j) && new_main_diag <0) possible =0;
        if((i + j ==3) && new_anti_diag <0) possible =0;
        if(!possible) continue;
        // Assign
        M[i][j] = val;
        row_left[i] -= val;
        col_left_left[j] -= val;
        if(i == j) main_diag_left -= val;
        if(i + j ==3) anti_diag_left -= val;
        // Recurse
        backtrack(idx+1);
        // Backtrack
        M[i][j] = 0;
        row_left[i] += val;
        col_left_left[j] += val;
        if(i == j) main_diag_left += val;
        if(i + j ==3) anti_diag_left += val;
    }
}

int main(){
    // Initialize M to 0
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            M[i][j] = 0;
        }
    }
    // Read row sums
    for(int i=0;i<4;i++) scanf("%d", &row_sums[i]);
    // Read column sums
    for(int i=0;i<4;i++) scanf("%d", &col_sums[i]);
    // Read diagonals
    scanf("%d", &main_diag_sum);
    scanf("%d", &anti_diag_sum);
    // Read 4 triplets
    for(int t=0;t<4;t++) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        M[i][j] = k;
    }
    // Initialize row_left and col_left
    for(int i=0;i<4;i++) {
        row_left[i] = row_sums[i];
        col_left_left[i] = col_sums[i];
    }
    main_diag_left = main_diag_sum;
    anti_diag_left = anti_diag_sum;
    // Subtract known cells
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(M[i][j] >0){
                row_left[i] -= M[i][j];
                col_left_left[j] -= M[i][j];
                if(i == j) main_diag_left -= M[i][j];
                if(i + j ==3) anti_diag_left -= M[i][j];
            }
        }
    }
    // Collect remaining cells
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(M[i][j] ==0){
                rem[rem_cnt].i = i;
                rem[rem_cnt].j = j;
                rem_cnt++;
            }
        }
    }
    // Start backtracking
    backtrack(0);
    return 0;
}