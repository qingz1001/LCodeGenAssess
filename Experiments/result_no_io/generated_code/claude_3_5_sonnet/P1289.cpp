#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005

int N, K;
int S[MAX_N], pos[MAX_N], target[MAX_N];
int occupied[MAX_N], empty[MAX_N];

int main() {
    scanf("%d %d", &N, &K);
    
    int total_blocks = 0;
    for (int i = 1; i <= K; i++) {
        scanf("%d", &S[i]);
        total_blocks += S[i];
        for (int j = 0; j < S[i]; j++) {
            int block;
            scanf("%d", &block);
            pos[total_blocks - S[i] + j + 1] = block;
            occupied[block] = 1;
        }
    }
    
    int empty_count = 0;
    for (int i = 1; i <= N; i++) {
        if (!occupied[i]) {
            empty[++empty_count] = i;
        }
    }
    
    for (int i = 1; i <= total_blocks; i++) {
        target[i] = i;
    }
    
    int moves = 0;
    for (int i = 1; i <= total_blocks; i++) {
        if (pos[i] != target[i]) {
            moves++;
            int j = i + 1;
            while (j <= total_blocks && pos[j] != target[i]) {
                j++;
            }
            
            if (j <= total_blocks) {
                int temp = pos[j];
                pos[j] = pos[i];
                pos[i] = temp;
            } else {
                pos[i] = empty[empty_count--];
                i--;
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