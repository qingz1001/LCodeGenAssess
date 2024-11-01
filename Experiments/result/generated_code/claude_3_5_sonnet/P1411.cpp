#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 701
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n;
int adj[MAX_N][MAX_N];
int size[MAX_N];
long long dp[MAX_N][2];

void dfs(int u, int parent) {
    size[u] = 1;
    dp[u][0] = 1;
    dp[u][1] = 1;
    
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] && v != parent) {
            dfs(v, u);
            size[u] += size[v];
            dp[u][0] *= MAX(dp[v][0], dp[v][1]);
            dp[u][1] *= dp[v][0];
        }
    }
    
    dp[u][1] *= size[u];
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }
    
    dfs(1, 0);
    
    printf("%lld\n", MAX(dp[1][0], dp[1][1]));
    
    return 0;
}