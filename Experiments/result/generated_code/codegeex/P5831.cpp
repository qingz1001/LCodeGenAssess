#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    
    int ranks[K][N];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &ranks[i][j]);
        }
    }
    
    int consistent_pairs = 0;
    for (int i = 1; i <= N; i++) {
        int is_consistent = 1;
        for (int k = 0; k < K; k++) {
            int j;
            for (j = 0; j < N; j++) {
                if (ranks[k][j] == i) {
                    break;
                }
            }
            if (j != 0 && ranks[k][j-1] < i) {
                is_consistent = 0;
                break;
            }
        }
        if (is_consistent) {
            consistent_pairs++;
        }
    }
    
    printf("%d\n", consistent_pairs);
    return 0;
}