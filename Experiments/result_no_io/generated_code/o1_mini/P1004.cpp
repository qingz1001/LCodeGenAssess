#include <stdio.h>
#include <string.h>

#define MAXN 10
#define MAXK 18
#define INF -1000000000

int grid[MAXN][MAXN];
int dp[MAXK+1][MAXN][MAXN];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int N;
    scanf("%d", &N);
    memset(grid, 0, sizeof(grid));
    while(1){
        int x, y, val;
        if(scanf("%d", &x)!=1) break;
        if(x == 0) break;
        scanf("%d %d", &y, &val);
        grid[x][y] = val;
    }
    
    for(int k=0; k<=2*N; k++){
        for(int x1=1; x1<=N; x1++){
            for(int x2=1; x2<=N; x2++){
                dp[k][x1][x2] = INF;
            }
        }
    }
    dp[2][1][1] = grid[1][1];
    for(int k=2; k<2*N; k++){
        for(int x1=1; x1<=N; x1++){
            for(int x2=1; x2<=N; x2++){
                if(x1 + x2 -2 != k-1) continue;
                if(dp[k][x1][x2] == INF) continue;
                // Next step
                for(int dx1=0; dx1<=1; dx1++){
                    for(int dx2=0; dx2<=1; dx2++){
                        int nx1 = x1 + dx1;
                        int ny1 = (k - x1) + 1 + (1 - dx1);
                        int nx2 = x2 + dx2;
                        int ny2 = (k - x2) + 1 + (1 - dx2);
                        if(nx1 <1 || nx1 >N || ny1 <1 || ny1 >N) continue;
                        if(nx2 <1 || nx2 >N || ny2 <1 || ny2 >N) continue;
                        int add;
                        if(nx1 == nx2 && ny1 == ny2){
                            add = grid[nx1][ny1];
                        }
                        else{
                            add = grid[nx1][ny1] + grid[nx2][ny2];
                        }
                        if(dp[k+1][nx1][nx2] < dp[k][x1][x2] + add){
                            dp[k+1][nx1][nx2] = dp[k][x1][x2] + add;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", dp[2*N][N][N]);
    return 0;
}