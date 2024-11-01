#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20
#define INF 1000000000

int n;
int dist_matrix[MAXN][MAXN];
int dp_size;
int *dp;
int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &dist_matrix[i][j]);
        }
    }
    dp_size = 1 << n;
    dp = (int*)malloc(dp_size * n * sizeof(int));
    for(int i=0;i<dp_size * n;i++) dp[i] = INF;
    // Starting at village 0
    dp[1 << 0 * n + 0] = 0;
    for(int mask=0; mask < (1 << n); mask++) {
        for(int u=0; u<n; u++) {
            if((mask & (1 << u)) ){
                for(int v=0; v<n; v++) {
                    if(!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        int current = dp[mask * n + u] + dist_matrix[u][v];
                        if(current < dp[next_mask * n + v]){
                            dp[next_mask * n + v] = current;
                        }
                    }
                }
            }
        }
    }
    int final_mask = (1 << n) -1;
    int res = INF;
    for(int u=0; u<n; u++) {
        if(u ==0) continue;
        if(dp[final_mask * n + u] + dist_matrix[u][0] < res){
            res = dp[final_mask * n + u] + dist_matrix[u][0];
        }
    }
    printf("%d\n", res);
    free(dp);
    return 0;
}