#include <stdio.h>

#define MAX_K 10
#define MAX_N 20

int main() {
    int K, N;
    int rankings[MAX_K][MAX_N];
    int consistent = 0;
    
    scanf("%d %d", &K, &N);
    
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &rankings[i][j]);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;
            
            int always_better = 1;
            for (int k = 0; k < K; k++) {
                int pos_i = -1, pos_j = -1;
                for (int l = 0; l < N; l++) {
                    if (rankings[k][l] == i) pos_i = l;
                    if (rankings[k][l] == j) pos_j = l;
                }
                if (pos_i > pos_j) {
                    always_better = 0;
                    break;
                }
            }
            if (always_better) consistent++;
        }
    }
    
    printf("%d\n", consistent);
    
    return 0;
}