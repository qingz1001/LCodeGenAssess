#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int n, m;
int matrix[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

int main() {
    scanf("%d %d", &n, &m);
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int max_side = 0;
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(matrix[i][j] == 1) {
                dp[i][j] = MIN(MIN(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                if(dp[i][j] > max_side) {
                    max_side = dp[i][j];
                }
            }
        }
    }
    
    printf("%d\n", max_side);
    
    return 0;
}