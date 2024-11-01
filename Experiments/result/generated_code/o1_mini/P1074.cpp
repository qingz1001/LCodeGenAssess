#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int r;
    int c;
    int score;
} Cell;

int grid[9][9];
int score_grid[9][9];
int rows[9][10];
int cols[9][10];
int blocks[9][10];
Cell empty_cells[81];
long long remain_max[81];
int cell_count = 0;
long long maximum_sum = -1;

int cmp(const void* a, const void* b) {
    Cell* ca = (Cell*)a;
    Cell* cb = (Cell*)b;
    if (cb->score != ca->score)
        return cb->score - ca->score;
    return 0;
}

void backtrack(int pos, long long current_sum) {
    if (pos == cell_count) {
        if (current_sum > maximum_sum)
            maximum_sum = current_sum;
        return;
    }
    if (current_sum + remain_max[pos] <= maximum_sum)
        return;
    int r = empty_cells[pos].r;
    int c = empty_cells[pos].c;
    int b = (r / 3) * 3 + (c / 3);
    for (int num = 9; num >=1; num--){
        if (!rows[r][num] && !cols[c][num] && !blocks[b][num]){
            rows[r][num] = cols[c][num] = blocks[b][num] = 1;
            long long new_sum = current_sum + (long long)empty_cells[pos].score * num;
            backtrack(pos + 1, new_sum);
            rows[r][num] = cols[c][num] = blocks[b][num] = 0;
        }
    }
}

int main(){
    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++){
            scanf("%d", &grid[r][c]);
        }
    }
    // Compute score_grid
    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++){
            int layer = abs(r-4) > abs(c-4) ? abs(r-4) : abs(c-4);
            score_grid[r][c] = 10 - layer;
        }
    }
    // Initialize rows, cols, blocks and collect empty cells
    int valid = 1;
    for(int r=0;r<9 && valid;r++){
        for(int c=0;c<9 && valid;c++){
            int num = grid[r][c];
            if(num !=0){
                int b = (r / 3) * 3 + (c / 3);
                if(rows[r][num] || cols[c][num] || blocks[b][num]){
                    valid = 0;
                    break;
                }
                rows[r][num] = cols[c][num] = blocks[b][num] = 1;
            }
            else{
                empty_cells[cell_count].r = r;
                empty_cells[cell_count].c = c;
                empty_cells[cell_count].score = score_grid[r][c];
                cell_count++;
            }
        }
    }
    if(!valid){
        printf("-1\n");
        return 0;
    }
    // Sort empty_cells by score descending
    qsort(empty_cells, cell_count, sizeof(Cell), cmp);
    // Precompute remain_max
    if(cell_count >0){
        remain_max[cell_count -1] = (long long)empty_cells[cell_count -1].score * 9;
        for(int i=cell_count -2;i>=0;i--){
            remain_max[i] = (long long)empty_cells[i].score * 9 + remain_max[i+1];
        }
    }
    backtrack(0, 0);
    printf("%lld\n", maximum_sum);
    return 0;
}