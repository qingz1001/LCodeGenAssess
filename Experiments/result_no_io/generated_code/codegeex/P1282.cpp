#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *domino = (int *)malloc(2 * n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &domino[2 * i], &domino[2 * i + 1]);
    }
    
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (domino[2 * i] + domino[2 * i + 1] > max) {
            max = domino[2 * i] + domino[2 * i + 1];
        }
    }
    
    int **dp = (int **)malloc((max + 1) * sizeof(int *));
    for (int i = 0; i <= max; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int));
    }
    
    int diff = domino[0] - domino[1];
    for (int i = 1; i < n; i++) {
        int new_diff = diff + domino[2 * i] - domino[2 * i + 1];
        for (int j = 0; j <= max - new_diff; j++) {
            dp[j + new_diff][i + 1] = dp[j][i] + 1;
        }
        new_diff = diff - domino[2 * i] + domino[2 * i + 1];
        for (int j = 0; j <= max - new_diff; j++) {
            if (dp[j + new_diff][i + 1] > dp[j][i]) {
                dp[j + new_diff][i + 1] = dp[j][i];
            }
        }
        diff = new_diff;
    }
    
    int min_rotations = dp[0][n];
    for (int i = 1; i <= max; i++) {
        if (dp[i][n] < min_rotations) {
            min_rotations = dp[i][n];
        }
    }
    
    printf("%d\n", min_rotations);
    
    for (int i = 0; i <= max; i++) {
        free(dp[i]);
    }
    free(dp);
    free(domino);
    
    return 0;
}