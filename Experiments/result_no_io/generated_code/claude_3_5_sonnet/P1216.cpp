#include <stdio.h>
#include <stdlib.h>

#define MAX_R 1000

int main() {
    int r, i, j;
    int triangle[MAX_R][MAX_R] = {0};
    int dp[MAX_R][MAX_R] = {0};
    
    scanf("%d", &r);
    
    for (i = 0; i < r; i++) {
        for (j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }
    
    for (j = 0; j < r; j++) {
        dp[r-1][j] = triangle[r-1][j];
    }
    
    for (i = r-2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j] + (dp[i+1][j] > dp[i+1][j+1] ? dp[i+1][j] : dp[i+1][j+1]);
        }
    }
    
    printf("%d\n", dp[0][0]);
    
    return 0;
}