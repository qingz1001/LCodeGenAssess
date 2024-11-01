#include <stdio.h>
#include <stdlib.h>

#define MAX 200
#define MIN_INF (-1000000000)

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    long grid[MAX][MAX];
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            scanf("%ld", &grid[i][j]);
        }
    }

    long dp[MAX][MAX];
    for(int j=0; j<n; j++) {
        dp[m-1][j] = (j == n/2) ? grid[m-1][j] : MIN_INF;
    }

    for(int i=m-2;i>=0;i--){
        for(int j=0;j<n;j++){
            long max_prev = MIN_INF;
            if(j-1 >=0 && dp[i+1][j-1] > max_prev) max_prev = dp[i+1][j-1];
            if(dp[i+1][j] > max_prev) max_prev = dp[i+1][j];
            if(j+1 <n && dp[i+1][j+1] > max_prev) max_prev = dp[i+1][j+1];
            dp[i][j] = grid[i][j] + max_prev;
        }
    }

    long result = MIN_INF;
    for(int j=0; j<n; j++) {
        if(dp[0][j] > result) result = dp[0][j];
    }
    printf("%ld", result);
    return 0;
}