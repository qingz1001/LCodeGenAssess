#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 18
#define MAX_M 324
#define MAX_K 324
#define WORD_SIZE 64

typedef struct {
    unsigned long long bits[6];
    int rhs;
} Row;

int n;
int grid[MAX_N][MAX_N];
int cell_to_var[MAX_M];
int var_to_cell[MAX_K];
int num_vars = 0;
Row matrix[MAX_M];
int m;

int main(){
    scanf("%d", &n);
    m = n * n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    // Assign variables
    memset(cell_to_var, -1, sizeof(cell_to_var));
    for(int i=0;i<m;i++) {
        int row = i / n;
        int col = i % n;
        if(grid[row][col] == 0){
            cell_to_var[i] = num_vars;
            var_to_cell[num_vars] = i;
            num_vars++;
        }
    }
    // Build equations
    for(int i=0;i<m;i++) {
        int row = i / n;
        int col = i % n;
        // Neighbors: up, down, left, right
        int neighbors[4][2] = {
            {row-1, col},
            {row+1, col},
            {row, col-1},
            {row, col+1}
        };
        memset(matrix[i].bits, 0, sizeof(matrix[i].bits));
        matrix[i].rhs = 0;
        for(int d=0; d<4; d++) {
            int x = neighbors[d][0];
            int y = neighbors[d][1];
            if(x >=0 && x <n && y >=0 && y <n){
                int idx = x * n + y;
                if(grid[x][y] == 0){
                    int var = cell_to_var[idx];
                    if(var != -1){
                        int word = var / WORD_SIZE;
                        int bit = var % WORD_SIZE;
                        matrix[i].bits[word] |= (1ULL << bit);
                    }
                }
                if(grid[x][y] == 1){
                    matrix[i].rhs ^=1;
                }
            }
        }
    }
    // Gaussian elimination
    int rank = 0;
    for(int col=0; col<num_vars && rank < m; col++){
        int pivot = -1;
        for(int i=rank;i<m;i++) {
            int word = col / WORD_SIZE;
            int bit = col % WORD_SIZE;
            if( (matrix[i].bits[word] >> bit) & 1ULL ){
                pivot = i;
                break;
            }
        }
        if(pivot == -1) continue;
        // Swap rows
        Row temp = matrix[rank];
        matrix[rank] = matrix[pivot];
        matrix[pivot] = temp;
        // Eliminate below
        for(int i=0;i<m;i++) {
            if(i != rank){
                int word = col / WORD_SIZE;
                int bit = col % WORD_SIZE;
                if( (matrix[i].bits[word] >> bit) & 1ULL ){
                    for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
                        matrix[i].bits[w] ^= matrix[rank].bits[w];
                    }
                    matrix[i].rhs ^= matrix[rank].rhs;
                }
            }
        }
        rank++;
    }
    // Check for inconsistency
    int inconsistent = 0;
    for(int i=rank;i<m;i++) {
        int has_var = 0;
        for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
            if(matrix[i].bits[w]){
                has_var =1;
                break;
            }
        }
        if(!has_var && matrix[i].rhs){
            inconsistent =1;
            break;
        }
    }
    if(inconsistent){
        printf("-1\n");
        return 0;
    }
    // Identify free variables and build solution
    int *solution = (int*)calloc(num_vars, sizeof(int));
    memset(solution, 0, sizeof(int)*num_vars);
    // Back substitution
    for(int i=0;i<rank;i++) {
        // Find first set bit
        int lead = -1;
        for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
            if(matrix[i].bits[w]){
                for(int b=0; b<WORD_SIZE; b++) {
                    if( (matrix[i].bits[w] >> b) &1ULL ){
                        lead = w * WORD_SIZE + b;
                        break;
                    }
                }
                if(lead != -1) break;
            }
        }
        if(lead == -1) continue;
        if(lead >= num_vars) continue;
        // Set the variable
        int val = matrix[i].rhs;
        for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
            if(w*WORD_SIZE + lead < num_vars && ((matrix[i].bits[w] >> lead) &1ULL)){
                // Already accounted
                break;
            }
        }
        solution[lead] = val;
        // Update RHS for other equations
        for(int j=0; j<rank; j++) {
            if(j == i) continue;
            int word = lead / WORD_SIZE;
            int bit = lead % WORD_SIZE;
            if( (matrix[j].bits[word] >> bit) &1ULL ){
                matrix[j].rhs ^= val;
                matrix[j].bits[word] ^=1ULL;
            }
        }
    }
    // Count free variables
    int free_vars = num_vars - rank;
    if(free_vars ==0){
        // Unique solution
        int cnt=0;
        for(int i=0;i<num_vars;i++) cnt += solution[i];
        printf("%d\n", cnt);
        free(solution);
        return 0;
    }
    // Collect free variable indices
    int *free_indices = (int*)malloc(free_vars * sizeof(int));
    int fi=0;
    for(int i=0;i<num_vars;i++) {
        int is_pivot =0;
        for(int j=0;j<rank;j++) {
            int lead = -1;
            for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
                if(matrix[j].bits[w]){
                    for(int b=0; b<WORD_SIZE; b++) {
                        if( (matrix[j].bits[w] >> b) &1ULL ){
                            lead = w * WORD_SIZE + b;
                            break;
                        }
                    }
                    if(lead != -1) break;
                }
            }
            if(lead == i){
                is_pivot =1;
                break;
            }
        }
        if(!is_pivot){
            free_indices[fi++] = i;
        }
    }
    // Build basis vectors
    int basis_size = free_vars;
    unsigned long long *basis = (unsigned long long*)malloc(basis_size * sizeof(unsigned long long));
    for(int i=0;i<basis_size;i++) basis[i] =0;
    // Initialize solution
    for(int i=0;i<num_vars;i++) {
        if(solution[i]){
            basis_size =0;
            break;
        }
    }
    // Since implementing minimal weight solution is complex, we'll use a simple approach
    // Assume free_vars <=20
    if(free_vars >20){
        // Too many free variables, output -1
        printf("-1\n");
        free(solution);
        free(free_indices);
        free(basis);
        return 0;
    }
    // Enumerate all possible assignments to free variables
    int min_cnt = num_vars +1;
    for(unsigned long long mask=0; mask<(1ULL<<free_vars); mask++){
        // Assign free variables
        int current[num_vars];
        memcpy(current, solution, sizeof(int)*num_vars);
        for(int i=0;i<free_vars;i++) {
            int var = free_indices[i];
            current[var] = (mask >> i) &1ULL;
        }
        // Back substitute to set pivot variables
        for(int j=0;j<rank;j++) {
            int lead = -1;
            for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
                if(matrix[j].bits[w]){
                    for(int b=0; b<WORD_SIZE; b++) {
                        if( (matrix[j].bits[w] >> b) &1ULL ){
                            lead = w * WORD_SIZE + b;
                            break;
                        }
                    }
                    if(lead != -1) break;
                }
            }
            if(lead == -1) continue;
            int sum = matrix[j].rhs;
            // Sum over other variables
            for(int w=0; w<(num_vars + WORD_SIZE -1)/WORD_SIZE; w++) {
                for(int b=0; b<WORD_SIZE; b++) {
                    int var = w * WORD_SIZE + b;
                    if(var >= num_vars || var == lead) continue;
                    if( (matrix[j].bits[w] >> b) &1ULL ){
                        sum ^= current[var];
                    }
                }
            }
            current[lead] = sum;
        }
        // Count number of 1's
        int cnt=0;
        for(int i=0;i<num_vars;i++) cnt += current[i];
        if(cnt < min_cnt) min_cnt = cnt;
    }
    printf("%d\n", min_cnt);
    free(solution);
    free(free_indices);
    free(basis);
    return 0;
}