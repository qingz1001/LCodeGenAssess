#include <stdio.h>
#include <string.h>

int main(){
    int n, m, Cx, Cy;
    scanf("%d %d %d %d", &n, &m, &Cx, &Cy);
    
    // Initialize grid as not blocked
    int blocked[21][21];
    memset(blocked, 0, sizeof(blocked));
    
    // Directions for knight moves
    int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
    
    // Block the horse's position
    if(Cx >=0 && Cx <=n && Cy >=0 && Cy <=m){
        blocked[Cx][Cy] = 1;
    }
    
    // Block all positions the horse can reach
    for(int i=0;i<8;i++){
        int nx = Cx + dx[i];
        int ny = Cy + dy[i];
        if(nx >=0 && nx <=n && ny >=0 && ny <=m){
            blocked[nx][ny] = 1;
        }
    }
    
    // Initialize DP table
    long long dp[21][21];
    memset(dp, 0, sizeof(dp));
    
    if(!blocked[0][0]){
        dp[0][0] = 1;
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(blocked[i][j]) continue;
            if(i > 0){
                dp[i][j] += dp[i-1][j];
            }
            if(j > 0){
                dp[i][j] += dp[i][j-1];
            }
        }
    }
    
    printf("%lld\n", dp[n][m]);
    return 0;
}