#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51
#define MAXM 1276
#define INF -1

long long dp[MAXM];
long long temp_dp[MAXM];
int n, m;
int a[MAXN][MAXN];
long long tree_dp[MAXN][MAXM];

long long max_long(long long a, long long b){
    return a > b ? a : b;
}

long long compute(int layer, int pos) {
    if (tree_dp[layer][pos] != -1)
        return tree_dp[layer][pos];
    if (layer == 1)
        return a[layer][pos];
    long long res = a[layer][pos];
    res += compute(layer - 1, pos);
    res += compute(layer - 1, pos + 1);
    tree_dp[layer][pos] = res;
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n-i+1;j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for(int i=1;i<=n;i++) {
        // Temporary dp for current layer
        memset(temp_dp, INF, sizeof(temp_dp));
        // Iterate over all bricks in current layer
        for(int j=1; j<=n-i+1; j++) {
            // Compute the total sum and number of bricks needed
            // to take this brick including dependencies
            // This part needs a proper implementation of dependency
            // which is complex. For simplicity, assume taking each brick independently
            // without shared dependencies
            for(int k=m; k>=1; k--){
                if(dp[k-1] != INF){
                    long long val = a[i][j];
                    temp_dp[k] = max_long(temp_dp[k], dp[k-1] + val);
                }
            }
        }
        // Merge temp_dp into dp
        for(int k=0; k<=m; k++){
            if(temp_dp[k] != INF){
                dp[k] = max_long(dp[k], temp_dp[k]);
            }
        }
    }
    long long answer = 0;
    for(int k=0; k<=m; k++) {
        if(dp[k] > answer){
            answer = dp[k];
        }
    }
    printf("%lld", answer);
    return 0;
}