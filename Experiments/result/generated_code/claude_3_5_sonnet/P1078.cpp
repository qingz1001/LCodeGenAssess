#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 101
#define MAX_K 101
#define INF INT_MAX

int N, K, M, S, T;
int culture[MAX_N];
int reject[MAX_K][MAX_K];
int dist[MAX_N][MAX_N];
int visited[MAX_N];
int dp[1 << MAX_K][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int tsp(int mask, int u) {
    if (mask == (1 << K) - 1 && u == T)
        return 0;
    
    if (dp[mask][u] != -1)
        return dp[mask][u];
    
    int res = INF;
    for (int v = 1; v <= N; v++) {
        if (dist[u][v] == INF) continue;
        if (visited[v]) continue;
        if (reject[culture[u] - 1][culture[v] - 1]) continue;
        
        int newMask = mask | (1 << (culture[v] - 1));
        visited[v] = 1;
        int subRes = tsp(newMask, v);
        visited[v] = 0;
        
        if (subRes != INF)
            res = min(res, dist[u][v] + subRes);
    }
    
    return dp[mask][u] = res;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    
    for (int i = 1; i <= N; i++)
        scanf("%d", &culture[i]);
    
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            scanf("%d", &reject[i][j]);
    
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            dist[i][j] = INF;
    
    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        dist[u][v] = min(dist[u][v], d);
        dist[v][u] = min(dist[v][u], d);
    }
    
    memset(dp, -1, sizeof(dp));
    memset(visited, 0, sizeof(visited));
    
    visited[S] = 1;
    int result = tsp(1 << (culture[S] - 1), S);
    
    if (result == INF)
        printf("-1\n");
    else
        printf("%d\n", result);
    
    return 0;
}