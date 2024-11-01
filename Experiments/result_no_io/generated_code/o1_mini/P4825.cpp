#include <stdio.h>
#define MOD 1000000007
int main(){
    int R, C, K;
    scanf("%d %d %d", &R, &C, &K);
    int grid[R][C];
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    long long DP[R][C];
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(i ==0 && j ==0){
                DP[i][j] =1;
            }
            else{
                DP[i][j] =0;
                for(int x=0;x<i;x++) {
                    for(int y=0;y<j;y++) {
                        if(grid[x][y] != grid[i][j]){
                            DP[i][j] += DP[x][y];
                            if(DP[i][j] >= MOD) DP[i][j] -= MOD;
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", DP[R-1][C-1]%MOD);
}