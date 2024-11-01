#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

typedef long long ll;

int main(){
    int n, m;
    ll k;
    scanf("%d %d %lld", &n, &m, &k);
    
    int x, y;
    scanf("%d %d", &x, &y);
    
    int p;
    scanf("%d", &p);
    
    int police[MAX][MAX];
    memset(police, 0, sizeof(police));
    for(int i=0;i<p;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        police[a][b] = 1;
    }
    
    // Directions: 0=North,1=East,2=South,3=West
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    ll dp[MAX][MAX][4];
    memset(dp, 0, sizeof(dp));
    
    // Starting at (n,1) facing North
    dp[n][1][0] = 1;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int d=0; d<4; d++){
                if(dp[i][j][d]==0) continue;
                if(police[i][j]) continue;
                
                // Straight
                int nd1 = d;
                int ni1 = i + dx[nd1];
                int nj1 = j + dy[nd1];
                if(ni1 >=1 && ni1 <=n && nj1 >=1 && nj1 <=m && !police[ni1][nj1]){
                    dp[ni1][nj1][nd1] = (dp[ni1][nj1][nd1] + dp[i][j][d]) % k;
                }
                
                // Right turn
                int nd2 = (d + 1) % 4;
                int ni2 = i + dx[nd2];
                int nj2 = j + dy[nd2];
                if(ni2 >=1 && ni2 <=n && nj2 >=1 && nj2 <=m && !police[ni2][nj2]){
                    dp[ni2][nj2][nd2] = (dp[ni2][nj2][nd2] + dp[i][j][d]) % k;
                }
            }
        }
    }
    
    ll result = 0;
    for(int d=0; d<4; d++) {
        result = (result + dp[x][y][d]) % k;
    }
    
    printf("%lld\n", result);
    return 0;
}