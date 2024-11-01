#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    int* blocks = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        blocks[i] = -1;
    }
    
    int moves = 0;
    for (int i = 0; i < K; i++) {
        int S_i;
        scanf("%d", &S_i);
        int* file_blocks = (int*)malloc(S_i * sizeof(int));
        for (int j = 0; j < S_i; j++) {
            scanf("%d", &file_blocks[j]);
        }
        
        int start = -1;
        for (int j = 0; j < S_i; j++) {
            if (blocks[file_blocks[j] - 1] == -1) {
                if (start == -1) {
                    start = file_blocks[j];
                } else {
                    moves += abs(file_blocks[j] - start);
                    start = file_blocks[j];
                }
            }
        }
        
        free(file_blocks);
    }
    
    printf("We need %d move operations.\n", moves);
    
    free(blocks);
    return 0;
}