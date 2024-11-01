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
    
    int consistentPairs = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            
            int cowA = rankings[0][i];
            int cowB = rankings[0][j];
            int isConsistent = 1;
            
            for (int k = 1; k < K; k++) {
                int posA = -1, posB = -1;
                for (int l = 0; l < N; l++) {
                    if (rankings[k][l] == cowA) posA = l;
                    if (rankings[k][l] == cowB) posB = l;
                }
                if (posA >= posB) {
                    isConsistent = 0;
                    break;
                }
            }
            
            if (isConsistent) {
                consistentPairs++;
            }
        }
    }
    
    printf("%d\n", consistentPairs);
    
    return 0;
}