#include <stdio.h>
#include <stdlib.h>

#define MAX_M 6
#define MAX_STATE (1 << MAX_M)

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N, M;
        scanf("%d %d", &N, &M);
        int grid[N][M];
        for(int i =0;i<N;i++) {
            for(int j=0; j<M; j++) {
                scanf("%d", &grid[i][j]);
            }
        }
        long long dp[N+1][MAX_STATE];
        for(int i=0;i<=N;i++) {
            for(int s=0;s<(1<<M);s++) {
                dp[i][s] = -1;
            }
        }
        dp[0][0] = 0;
        for(int i=0;i<N;i++) {
            for(int prev=0; prev<(1<<M); prev++) {
                if(dp[i][prev]==-1) continue;
                for(int curr=0; curr<(1<<M); curr++) {
                    // Check no two bits in curr are adjacent
                    if(curr & (curr <<1)) continue;
                    // Check no diagonally adjacent with prev
                    if( (curr & (prev)) ) continue;
                    if( (curr & (prev <<1)) ) continue;
                    if( (curr & (prev >>1)) ) continue;
                    // Calculate sum
                    int sum =0;
                    for(int j=0; j<M; j++) {
                        if(curr & (1<<j)) sum += grid[i][j];
                    }
                    if(dp[i+1][curr] < dp[i][prev] + sum){
                        dp[i+1][curr] = dp[i][prev] + sum;
                    }
                }
            }
        }
        long long res = 0;
        for(int s=0; s<(1<<M); s++) {
            if(dp[N][s] > res) res = dp[N][s];
        }
        printf("%lld\n", res);
    }
    return 0;
}