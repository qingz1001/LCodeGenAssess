#include <stdio.h>
#include <string.h>

#define MAX 101
#define DIR 4

long long dp[MAX][MAX][DIR];
char grid[MAX][MAX];
int n, m, k;
int target_x, target_y;

int main(){
    int x, y;
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);
    target_x = x;
    target_y = y;
    for(int i=1;i<=n;i++){
        scanf("%s", grid[i]+1);
    }
    // Directions: 0 - north, 1 - east, 2 - south, 3 - west
    // Starting at (n,1) facing north
    dp[n][1][0] = 1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int d=0; d<DIR; d++){
                if(dp[i][j][d]==0) continue;
                // Move straight
                int ni = i, nj = j;
                if(d == 0) ni = i-1;
                else if(d == 1) nj = j+1;
                else if(d == 2) ni = i+1;
                else if(d == 3) nj = j-1;
                if(ni >=1 && ni <=n && nj >=1 && nj <=m && grid[ni][nj] != '*'){
                    dp[ni][nj][d] = (dp[ni][nj][d] + dp[i][j][d]) % k;
                }
                // Turn right
                int nd = (d + 1) % 4;
                ni = i; nj = j;
                if(nd == 0) ni = i-1;
                else if(nd == 1) nj = j+1;
                else if(nd == 2) ni = i+1;
                else if(nd == 3) nj = j-1;
                if(ni >=1 && ni <=n && nj >=1 && nj <=m && grid[ni][nj] != '*'){
                    dp[ni][nj][nd] = (dp[ni][nj][nd] + dp[i][j][d]) % k;
                }
            }
        }
    }
    long long result = 0;
    for(int d=0; d<DIR; d++) {
        result = (result + dp[target_x][target_y][d]) % k;
    }
    printf("%lld", result);
}