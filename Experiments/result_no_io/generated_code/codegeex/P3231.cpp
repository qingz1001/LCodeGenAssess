#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int D;
    scanf("%d", &D);
    
    while (D--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        
        int grid[a][b][c];
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    scanf("%d", &grid[i][j][k]);
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                int prefix[c];
                for (int k = 0; k < c; k++) {
                    if (grid[i][j][k]) {
                        if (k > 0) {
                            prefix[k] = prefix[k-1] + 1;
                        } else {
                            prefix[k] = 1;
                        }
                    } else {
                        if (k > 0) {
                            prefix[k] = prefix[k-1];
                        } else {
                            prefix[k] = 0;
                        }
                    }
                }
                
                for (int k = 0; k < c; k++) {
                    if (grid[i][j][k]) {
                        int minVal = prefix[k];
                        if (k > 0) {
                            minVal = min(minVal, k + 1 - prefix[k]);
                        }
                        ans += minVal;
                    }
                }
            }
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}