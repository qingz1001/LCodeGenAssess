#include <stdio.h>
#include <stdlib.h>

int N;
int grid[81];
int neighbors[81][4];
int neighbor_counts[81];
int max_sum = -262145; // -32767 * 8 (since N<=9, max cells=81)

void dfs(int k, unsigned long long mask1, unsigned long long mask2, int current_sum){
    for(int i=0;i<neighbor_counts[k];i++){
        int neighbor = neighbors[k][i];
        if(neighbor < 64){
            unsigned long long bit = 1ULL << neighbor;
            if(!(mask1 & bit)){
                int new_sum = current_sum + grid[neighbor];
                if(new_sum > max_sum){
                    max_sum = new_sum;
                }
                dfs(neighbor, mask1 | bit, mask2, new_sum);
            }
        }
        else{
            unsigned long long bit = 1ULL << (neighbor - 64);
            if(!(mask2 & bit)){
                int new_sum = current_sum + grid[neighbor];
                if(new_sum > max_sum){
                    max_sum = new_sum;
                }
                dfs(neighbor, mask1, mask2 | bit, new_sum);
            }
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &grid[i*N + j]);
        }
    }
    // Precompute neighbors
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int k = i*N + j;
            neighbor_counts[k] = 0;
            if(i > 0){
                neighbors[k][neighbor_counts[k]++] = (i-1)*N + j;
            }
            if(i < N-1){
                neighbors[k][neighbor_counts[k]++] = (i+1)*N + j;
            }
            if(j > 0){
                neighbors[k][neighbor_counts[k]++] = i*N + (j-1);
            }
            if(j < N-1){
                neighbors[k][neighbor_counts[k]++] = i*N + (j+1);
            }
        }
    }
    for(int k=0;k<N*N;k++){
        unsigned long long mask1 = 0, mask2 = 0;
        if(k < 64){
            mask1 |= (1ULL << k);
        }
        else{
            mask2 |= (1ULL << (k - 64));
        }
        if(grid[k] > max_sum){
            max_sum = grid[k];
        }
        dfs(k, mask1, mask2, grid[k]);
    }
    printf("%d\n", max_sum);
    return 0;
}