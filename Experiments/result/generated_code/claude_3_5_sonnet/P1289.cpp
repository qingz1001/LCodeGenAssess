#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_K 100000

int N, K;
int S[MAX_K];
int blocks[MAX_K][MAX_N];
int current[MAX_N];
int target[MAX_N];

int main() {
    scanf("%d %d", &N, &K);
    
    int total_blocks = 0;
    for (int i = 0; i < K; i++) {
        scanf("%d", &S[i]);
        total_blocks += S[i];
        for (int j = 0; j < S[i]; j++) {
            scanf("%d", &blocks[i][j]);
            current[blocks[i][j] - 1] = i + 1;
        }
    }
    
    int index = 0;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < S[i]; j++) {
            target[index++] = i + 1;
        }
    }
    
    int moves = 0;
    for (int i = 0; i < N; i++) {
        if (current[i] != target[i]) {
            if (current[i] != 0 && target[i] != 0) {
                moves++;
            }
        }
    }
    
    if (moves == 0) {
        printf("No optimization needed.\n");
    } else {
        printf("We need %d move operations.\n", moves);
    }
    
    return 0;
}