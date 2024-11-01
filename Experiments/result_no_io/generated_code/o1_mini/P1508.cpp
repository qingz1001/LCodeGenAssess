#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

long long grid[MAX][MAX];
long long dp[MAX][MAX];
int m, n;

int main(){
    scanf("%d %d", &m, &n);
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            scanf("%lld", &grid[i][j]);
        }
    }
    // Initialize dp with -inf
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            dp[i][j] = -9223372036854775807LL;
        }
    }
    int start_col = n / 2;
    dp[m-1][start_col] = grid[m-1][start_col];
    for(int i=m-2;i>=0;i--){
        for(int j=0;j<n;j++){
            if(dp[i+1][j] != -9223372036854775807LL){
                if(dp[i][j] < dp[i+1][j] + grid[i][j]){
                    dp[i][j] = dp[i+1][j] + grid[i][j];
                }
            }
            if(j > 0 && dp[i+1][j-1] != -9223372036854775807LL){
                if(dp[i][j] < dp[i+1][j-1] + grid[i][j]){
                    dp[i][j] = dp[i+1][j-1] + grid[i][j];
                }
            }
            if(j < n-1 && dp[i+1][j+1] != -9223372036854775807LL){
                if(dp[i][j] < dp[i+1][j+1] + grid[i][j]){
                    dp[i][j] = dp[i+1][j+1] + grid[i][j];
                }
            }
        }
    }
    long long result = -9223372036854775807LL;
    for(int j=0;j<n;j++){
        if(dp[0][j] > result){
            result = dp[0][j];
        }
    }
    printf("%lld\n", result);
    return 0;
}