#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int* files = (int*)malloc((K + 1) * sizeof(int));
    int* positions = (int*)malloc(N * sizeof(int));
    int* target = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        positions[i] = -1;
        target[i] = -1;
    }

    int total_blocks = 0;
    for (int i = 0; i < K; i++) {
        int S_i;
        scanf("%d", &S_i);
        files[i] = S_i;
        total_blocks += S_i;
        for (int j = 0; j < S_i; j++) {
            int block;
            scanf("%d", &block);
            positions[block - 1] = i;
        }
    }

    int current_block = 0;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < files[i]; j++) {
            target[current_block++] = i;
        }
    }

    int moves = 0;
    for (int i = 0; i < total_blocks; i++) {
        if (positions[i] != target[i]) {
            moves++;
        }
    }

    if (moves == 0) {
        printf("No optimization needed.\n");
    } else {
        printf("We need %d move operations.\n", moves);
    }

    free(files);
    free(positions);
    free(target);

    return 0;
}