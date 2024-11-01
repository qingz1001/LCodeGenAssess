#include <stdio.h>
#include <string.h>

int main(){
    int n, m, hx, hy;
    scanf("%d %d %d %d", &n, &m, &hx, &hy);
    
    // Initialize blocked grid
    int blocked[21][21];
    memset(blocked, 0, sizeof(blocked));
    
    // Mark horse position
    if(hx >=0 && hx <=n && hy >=0 && hy <=m){
        blocked[hx][hy] = 1;
    }
    
    // Knight moves
    int moves[8][2] = {
        {2,1},{1,2},{-1,2},{-2,1},
        {-2,-1},{-1,-2},{1,-2},{2,-1}
    };
    for(int i=0;i<8;i++){
        int nx = hx + moves[i][0];
        int ny = hy + moves[i][1];
        if(nx >=0 && nx <=n && ny >=0 && ny <=m){
            blocked[nx][ny] = 1;
        }
    }
    
    // DP array
    unsigned long long dp[21][21];
    memset(dp, 0, sizeof(dp));
    
    if(!blocked[0][0]){
        dp[0][0] = 1;
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(blocked[i][j]){
                dp[i][j] = 0;
                continue;
            }
            if(i >0){
                dp[i][j] += dp[i-1][j];
            }
            if(j >0){
                dp[i][j] += dp[i][j-1];
            }
        }
    }
    
    printf("%llu\n", dp[n][m]);
    return 0;
}