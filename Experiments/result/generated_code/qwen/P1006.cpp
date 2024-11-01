#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    int** dp1 = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp1[i] = (int*)calloc(n + 1, sizeof(int));
    }
    
    int** dp2 = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp2[i] = (int*)calloc(n + 1, sizeof(int));
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp1[i][j] = MAX(dp1[i - 1][j], dp1[i][j - 1]) + grid[i - 1][j - 1];
        }
    }
    
    for (int i = m; i >= 1; i--) {
        for (int j = n; j >= 1; j--) {
            dp2[i][j] = MAX(dp2[i + 1][j], dp2[i][j + 1]) + grid[i - 1][j - 1];
        }
    }
    
    printf("%d\n", dp1[m][n] + dp2[1][1]);
    
    for (int i = 0; i <= m; i++) {
        free(dp1[i]);
        free(dp2[i]);
    }
    free(dp1);
    free(dp2);
    
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return 0;
}