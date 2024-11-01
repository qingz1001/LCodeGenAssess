#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long dp[31][31];
    for(int k=0; k<=m; k++){
        for(int i=1; i<=n; i++){
            dp[k][i] = 0;
        }
    }
    dp[0][1] = 1;
    for(int k=1; k<=m; k++){
        for(int i=1; i<=n; i++){
            int left = (i ==1) ? n : i-1;
            int right = (i ==n) ? 1 : i+1;
            dp[k][i] = dp[k-1][left] + dp[k-1][right];
        }
    }
    printf("%ld\n", dp[m][1]);
    return 0;
}