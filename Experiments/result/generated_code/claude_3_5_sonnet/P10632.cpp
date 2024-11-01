#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30001

int n;
int adj[MAX_N][MAX_N];
int deg[MAX_N];
double dp[MAX_N];
int size[MAX_N];

void dfs(int u, int p) {
    size[u] = 1;
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (v != p) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

double solve(int u, int p) {
    if (dp[u] >= 0) return dp[u];
    
    dp[u] = n;
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (v != p) {
            dp[u] += solve(v, u);
        }
    }
    dp[u] /= deg[u] + 1;
    
    return dp[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][deg[a]++] = b;
        adj[b][deg[b]++] = a;
    }
    
    dfs(0, -1);
    
    memset(dp, -1, sizeof(dp));
    double result = solve(0, -1);
    
    printf("%.4f\n", result);
    
    return 0;
}