#include <stdio.h>

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    
    int rankings[10][20];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &rankings[i][j]);
        }
    }
    
    int consistent_pairs = 0;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i != j) {
                int consistent = 1;
                for (int k = 0; k < K; k++) {
                    int pos_i = -1, pos_j = -1;
                    for (int l = 0; l < N; l++) {
                        if (rankings[k][l] == i) pos_i = l;
                        if (rankings[k][l] == j) pos_j = l;
                    }
                    if (pos_i >= pos_j) {
                        consistent = 0;
                        break;
                    }
                }
                if (consistent) {
                    consistent_pairs++;
                }
            }
        }
    }
    
    printf("%d\n", consistent_pairs);
    
    return 0;
}