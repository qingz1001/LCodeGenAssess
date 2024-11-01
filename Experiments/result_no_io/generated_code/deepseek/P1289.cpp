#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int start;
    int end;
} FileRange;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int *blocks = (int *)malloc(N * sizeof(int));
    FileRange *ranges = (FileRange *)malloc(K * sizeof(FileRange));

    for (int i = 0; i < N; i++) {
        blocks[i] = -1; // -1 indicates empty block
    }

    int total_blocks = 0;
    for (int i = 0; i < K; i++) {
        int S_i;
        scanf("%d", &S_i);
        ranges[i].start = total_blocks;
        ranges[i].end = total_blocks + S_i - 1;
        total_blocks += S_i;

        for (int j = 0; j < S_i; j++) {
            int block_id;
            scanf("%d", &block_id);
            blocks[block_id - 1] = i; // file index
        }
    }

    int moves = 0;
    for (int i = 0; i < K; i++) {
        for (int j = ranges[i].start; j <= ranges[i].end; j++) {
            if (blocks[j] != i) {
                moves++;
            }
        }
    }

    if (moves == 0) {
        printf("No optimization needed.\n");
    } else {
        printf("We need %d move operations.\n", moves);
    }

    free(blocks);
    free(ranges);

    return 0;
}