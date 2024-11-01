#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001

int n;
int parent[MAX_N];
int dp[MAX_N][3];

void dfs(int node) {
    dp[node][0] = 0;
    dp[node][1] = 1;
    dp[node][2] = 0;
    
    for (int child = node + 1; child <= n; child++) {
        if (parent[child] == node) {
            dfs(child);
            dp[node][0] += dp[child][1];
            dp[node][1] += (dp[child][0] < dp[child][2] ? dp[child][0] : dp[child][2]);
            dp[node][2] += (dp[child][1] < dp[child][0] ? dp[child][1] : dp[child][0]);
        }
    }
}

int main() {
    scanf("%d", &n);
    
    memset(parent, 0, sizeof(parent));
    for (int i = 2; i <= n; i++) {
        scanf("%d", &parent[i]);
    }
    
    dfs(1);
    
    int result = (dp[1][0] < dp[1][1] ? dp[1][0] : dp[1][1]);
    printf("%d\n", result);
    
    return 0;
}