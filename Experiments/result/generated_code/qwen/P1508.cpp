#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int n, m;
    scanf("%d %d", &m, &n);
    
    int **energy = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        energy[i] = (int *)malloc(n * sizeof(int));
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &energy[i][j]);
        }
    }
    
    int **dp = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = energy[i][j];
        }
    }
    
    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                dp[i][j] += MAX(dp[i + 1][j], dp[i + 1][j + 1]);
            } else if (j == n - 1) {
                dp[i][j] += MAX(dp[i + 1][j], dp[i + 1][j - 1]);
            } else {
                dp[i][j] += MAX(dp[i + 1][j], dp[i + 1][j - 1], dp[i + 1][j + 1]);
            }
        }
    }
    
    int max_energy = dp[0][(n - 1) / 2];
    printf("%d\n", max_energy);
    
    for (int i = 0; i < m; i++) {
        free(energy[i]);
        free(dp[i]);
    }
    free(energy);
    free(dp);
    
    return 0;
}