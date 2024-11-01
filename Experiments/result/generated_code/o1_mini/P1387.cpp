#include <stdio.h>

int min(int a, int b, int c) {
    if (a < b)
        return (a < c) ? a : c;
    else
        return (b < c) ? b : c;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[100][100];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    int dp[100][100];
    int max = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i ==0 || j ==0){
                dp[i][j] = matrix[i][j];
            }
            else if(matrix[i][j] ==1){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) +1;
            }
            else{
                dp[i][j] =0;
            }
            if(dp[i][j] > max){
                max = dp[i][j];
            }
        }
    }
    printf("%d", max);
    return 0;
}