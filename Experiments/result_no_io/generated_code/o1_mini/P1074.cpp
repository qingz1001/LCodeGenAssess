#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c;
    int block;
    int weight;
    int possible;
} Cell;

int grid[9][9];
int rows[9], cols[9], blocks[9];
int weight_grid[9][9];
Cell empty_cells[81];
int num_empty = 0;
long long max_score = -1;
long long current_score = 0;

// Comparator for sorting cells: first by weight descending, then by number of possible candidates
int cmp(const void *a, const void *b) {
    Cell *ca = (Cell*)a;
    Cell *cb = (Cell*)b;
    if(ca->weight != cb->weight)
        return cb->weight - ca->weight;
    return ca->possible - cb->possible;
}

int main(){
    // Initialize weight_grid
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            int dist = abs(r-4) > abs(c-4) ? abs(r-4) : abs(c-4);
            weight_grid[r][c] = 10 - dist;
            if(weight_grid[r][c] < 6) weight_grid[r][c] = 6;
        }
    }
    // Read input and set used numbers
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            scanf("%d", &grid[r][c]);
            if(grid[r][c] != 0){
                int num = grid[r][c];
                int b = (r/3)*3 + (c/3);
                rows[r] |= 1 << num;
                cols[c] |= 1 << num;
                blocks[b] |= 1 << num;
            }
        }
    }
    // Collect empty cells
    for(int r=0;r<9;r++) {
        for(int c=0;c<9;c++) {
            if(grid[r][c] == 0){
                empty_cells[num_empty].r = r;
                empty_cells[num_empty].c = c;
                empty_cells[num_empty].block = (r/3)*3 + (c/3);
                empty_cells[num_empty].weight = weight_grid[r][c];
                // Calculate possible candidates
                empty_cells[num_empty].possible = 0;
                for(int num=1;num<=9;num++) {
                    if( !(rows[r] & (1 << num)) && !(cols[c] & (1 << num)) && !(blocks[empty_cells[num_empty].block] & (1 << num)) ){
                        empty_cells[num_empty].possible++;
                    }
                }
                num_empty++;
            }
        }
    }
    // Sort empty cells
    qsort(empty_cells, num_empty, sizeof(Cell), cmp);
    
    // Backtracking function
    // index: current cell index
    // returns nothing, updates max_score
    // Implemented as nested function using recursion
    void backtrack(int index){
        if(index == num_empty){
            if(current_score > max_score){
                max_score = current_score;
            }
            return;
        }
        Cell cell = empty_cells[index];
        int r = cell.r;
        int c = cell.c;
        int b = cell.block;
        // Try numbers from 9 to 1 to maximize score early
        for(int num=9; num>=1; num--){
            if( !(rows[r] & (1 << num)) && !(cols[c] & (1 << num)) && !(blocks[b] & (1 << num)) ){
                // Assign
                rows[r] |= (1 << num);
                cols[c] |= (1 << num);
                blocks[b] |= (1 << num);
                current_score += (long long)num * weight_grid[r][c];
                // Recurse
                backtrack(index + 1);
                // Unassign
                rows[r] &= ~(1 << num);
                cols[c] &= ~(1 << num);
                blocks[b] &= ~(1 << num);
                current_score -= (long long)num * weight_grid[r][c];
            }
        }
    }
    
    backtrack(0);
    printf("%lld\n", max_score);
    return 0;
}