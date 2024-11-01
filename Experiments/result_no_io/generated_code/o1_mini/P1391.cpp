#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 18
#define MAX_K (MAX_N*MAX_N)
#define MAX_EQUATIONS (MAX_N*MAX_N)
#define WORD_SIZE 64

typedef unsigned long long ull;

typedef struct {
    ull bits[(MAX_K + 1 + WORD_SIZE - 1)/WORD_SIZE];
} Row;

int n;
int grid[MAX_N][MAX_N];
int var_map[MAX_N][MAX_N];
int var_count = 0;
Row matrix[MAX_EQUATIONS];
int equations = 0;

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &grid[i][j]);
            if(grid[i][j]==0){
                var_map[i][j] = var_count;
                var_count++;
            } else {
                var_map[i][j] = -1;
            }
        }
    }
    // Build equations
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            memset(&matrix[equations], 0, sizeof(Row));
            int c = 0;
            // Neighbors
            int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
            for(int d=0; d<4; d++){
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if(ni>=0 && ni<n && nj>=0 && nj<n){
                    if(grid[ni][nj]==1){
                        c ^= 1;
                    }
                    else{
                        int vid = var_map[ni][nj];
                        if(vid != -1){
                            int word = vid / WORD_SIZE;
                            int bit = vid % WORD_SIZE;
                            matrix[equations].bits[word] |= (1ULL << bit);
                        }
                    }
                }
            }
            // Set RHS
            if(c) {
                int word = var_count / WORD_SIZE;
                int bit = var_count % WORD_SIZE;
                if(word < (MAX_K +1 + WORD_SIZE -1)/WORD_SIZE){
                    matrix[equations].bits[word] |= (1ULL << bit);
                }
            }
            equations++;
        }
    }
    // Gaussian elimination
    int rank = 0;
    int where[MAX_K];
    memset(where, -1, sizeof(where));
    for(int col=0; col<var_count && rank < equations; col++){
        int sel = -1;
        for(int row=rank; row<equations; row++){
            int word = col / WORD_SIZE;
            int bit = col % WORD_SIZE;
            if(matrix[row].bits[word] & (1ULL << bit)){
                sel = row;
                break;
            }
        }
        if(sel == -1) continue;
        // Swap rows
        Row temp = matrix[rank];
        matrix[rank] = matrix[sel];
        matrix[sel] = temp;
        where[col] = rank;
        // Eliminate
        for(int row=0; row<equations; row++){
            if(row != rank){
                int word = col / WORD_SIZE;
                int bit = col % WORD_SIZE;
                if(matrix[row].bits[word] & (1ULL << bit)){
                    for(int w=0; w<(var_count +1 + WORD_SIZE -1)/WORD_SIZE; w++){
                        matrix[row].bits[w] ^= matrix[rank].bits[w];
                    }
                }
            }
        }
        rank++;
    }
    // Check for inconsistency
    int inconsistent = 0;
    for(int row=0; row<equations; row++){
        int all_zero = 1;
        for(int w=0; w<(var_count +1 + WORD_SIZE -1)/WORD_SIZE -1; w++) {
            if(matrix[row].bits[w] != 0){
                all_zero = 0;
                break;
            }
        }
        if(all_zero && (matrix[row].bits[(var_count)/WORD_SIZE] & (1ULL << (var_count % WORD_SIZE)))){
            inconsistent = 1;
            break;
        }
    }
    if(inconsistent){
        printf("-1");
        return 0;
    }
    // Extract solution
    int free_vars = 0;
    int free_list[MAX_K];
    for(int col=0; col<var_count; col++) {
        if(where[col]==-1){
            free_list[free_vars++] = col;
        }
    }
    // Initialize particular solution
    int solution[MAX_K];
    memset(solution, 0, sizeof(solution));
    for(int col=0; col<var_count; col++) {
        if(where[col] != -1){
            int row = where[col];
            int val = (matrix[row].bits[var_count / WORD_SIZE] >> (var_count % WORD_SIZE)) & 1;
            // Set based on RHS and known variables
            for(int c=0; c<var_count; c++) {
                if(c == col) continue;
                int word = c / WORD_SIZE;
                int bit = c % WORD_SIZE;
                if(matrix[row].bits[word] & (1ULL << bit)){
                    val ^= solution[c];
                }
            }
            solution[col] = val;
        }
    }
    // Basis vectors
    ull basis[free_vars];
    for(int i=0; i<free_vars; i++){
        basis[i] = 0;
        basis[i] |= (1ULL << free_list[i]);
        for(int col=0; col<var_count; col++) {
            if(where[col] != -1){
                int row = where[col];
                if(matrix[row].bits[free_list[i]/WORD_SIZE] & (1ULL << (free_list[i]%WORD_SIZE))){
                    basis[i] |= (1ULL << col);
                }
            }
        }
    }
    // Find minimum set bits
    int min_changes = 0;
    for(int i=0; i<var_count; i++) {
        if(solution[i]) min_changes++;
    }
    // Enumerate all possibilities if free_vars is small
    if(free_vars <= 20){
        int total = 1 << free_vars;
        for(int mask=1; mask<total; mask++){
            int cnt = 0;
            int tmp_solution[MAX_K];
            memcpy(tmp_solution, solution, sizeof(solution));
            for(int i=0; i<free_vars; i++) {
                if(mask & (1<<i)){
                    cnt++;
                    for(int bit=0; bit<var_count; bit++) {
                        if(basis[i] & (1ULL << bit)){
                            tmp_solution[bit] ^= 1;
                        }
                    }
                }
            }
            // Count
            int total_set = cnt;
            for(int i=0; i<var_count; i++) {
                if(tmp_solution[i]) total_set++;
            }
            if(total_set < min_changes){
                min_changes = total_set;
            }
        }
    }
    printf("%d", min_changes);
}