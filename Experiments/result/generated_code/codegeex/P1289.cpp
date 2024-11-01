#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int position;
} Block;

int compare(const void *a, const void *b) {
    Block *blockA = (Block *)a;
    Block *blockB = (Block *)b;
    return blockA->value - blockB->value;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    Block *blocks = (Block *)malloc(N * sizeof(Block));
    int *fileStarts = (int *)malloc(K * sizeof(int));
    int *fileSizes = (int *)malloc(K * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        blocks[i].value = 0;
        blocks[i].position = i + 1;
    }
    
    for (int i = 0; i < K; i++) {
        scanf("%d", &fileSizes[i]);
        for (int j = 0; j < fileSizes[i]; j++) {
            int block;
            scanf("%d", &block);
            blocks[block - 1].value = i + 1;
        }
    }
    
    qsort(blocks, N, sizeof(Block), compare);
    
    int moveCount = 0;
    int currentFile = 1;
    int currentPosition = 0;
    
    for (int i = 0; i < N; i++) {
        if (blocks[i].value == currentFile) {
            currentPosition++;
            if (currentPosition > fileStarts[currentFile - 1]) {
                moveCount++;
            }
        } else if (blocks[i].value == 0) {
            if (currentPosition < fileStarts[currentFile - 1]) {
                moveCount++;
            }
        }
    }
    
    if (moveCount == 0) {
        printf("No optimization needed.\n");
    } else {
        printf("We need %d move operations.\n", moveCount);
    }
    
    free(blocks);
    free(fileStarts);
    free(fileSizes);
    
    return 0;
}