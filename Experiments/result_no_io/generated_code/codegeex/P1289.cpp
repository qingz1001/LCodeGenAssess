#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    
    int *files = (int *)malloc(N * sizeof(int));
    int *positions = (int *)malloc(N * sizeof(int));
    int *moves = (int *)malloc(N * sizeof(int));
    
    int i, j, sum = 0;
    for (i = 0; i < K; i++) {
        int S;
        scanf("%d", &S);
        for (j = 0; j < S; j++) {
            scanf("%d", &files[sum + j]);
            positions[files[sum + j] - 1] = sum + j;
        }
        sum += S;
    }
    
    int min_moves = 0;
    for (i = 0; i < N; i++) {
        if (positions[i] != i) {
            int temp = files[i];
            int pos = positions[i];
            files[i] = files[pos];
            positions[files[i] - 1] = i;
            files[pos] = temp;
            positions[temp - 1] = pos;
            min_moves++;
        }
    }
    
    if (min_moves == 0) {
        printf("No optimization needed.\n");
    } else {
        printf("We need %d move operations.\n", min_moves);
    }
    
    free(files);
    free(positions);
    free(moves);
    
    return 0;
}