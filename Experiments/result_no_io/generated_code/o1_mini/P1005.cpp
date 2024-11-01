#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    ull power2[m+1];
    power2[0]=1;
    for(int k=1;k<=m;k++) power2[k]=power2[k-1]*2;
    ull total=0;
    for(int i=0;i<n;i++){
        ull dp[m+1][m+1];
        for(int l=0;l<=m;l++) {
            for(int r=0;r<=m;r++) dp[l][r]=0;
        }
        for(int len=1; len<=m; len++){
            for(int l=0; l + len <=m; l++){
                int r = l + len -1;
                int step = m - len +1;
                if(l==r){
                    dp[l][r] = (ull)matrix[i][l]*power2[step];
                }
                else{
                    ull pickL = (ull)matrix[i][l]*power2[step] + dp[l+1][r];
                    ull pickR = (ull)matrix[i][r]*power2[step] + dp[l][r-1];
                    dp[l][r] = pickL > pickR ? pickL : pickR;
                }
            }
        }
        total += dp[0][m-1];
    }
    printf("%llu\n", total);
    return 0;
}