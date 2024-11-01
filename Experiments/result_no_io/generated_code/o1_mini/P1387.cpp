#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int dp[n][m];
    int max = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(matrix[i][j]==1){
                if(i==0 || j==0){
                    dp[i][j]=1;
                }
                else{
                    int min = dp[i-1][j];
                    if(dp[i][j-1]<min) min = dp[i][j-1];
                    if(dp[i-1][j-1]<min) min = dp[i-1][j-1];
                    dp[i][j]=min+1;
                }
                if(dp[i][j] > max) max = dp[i][j];
            }
            else{
                dp[i][j]=0;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}