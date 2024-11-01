#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 101
#define MAX_K 101
#define INF INT_MAX

int N, K, M, S, T;
int culture[MAX_N];
int conflict[MAX_K][MAX_K];
int dist[MAX_N][MAX_N];
int dp[MAX_N][1 << MAX_K];
bool visited[MAX_N][1 << MAX_K];

int min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int cur, int state) {
    if (cur == T) return 0;
    if (visited[cur][state]) return dp[cur][state];
    
    visited[cur][state] = true;
    dp[cur][state] = INF;
    
    for (int next = 1; next <= N; next++) {
        if (dist[cur][next] == INF) continue;
        if (conflict[culture[cur]][culture[next]]) continue;
        if (state & (1 << culture[next])) continue;
        
        int new_state = state | (1 << culture[next]);
        int result = dfs(next, new_state);
        if (result != INF) {
            dp[cur][state] = min(dp[cur][state], result + dist[cur][next]);
        }
    }
    
    return dp[cur][state];
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &culture[i]);
        culture[i]--;
    }
    
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &conflict[i][j]);
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    
    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        dist[u][v] = min(dist[u][v], d);
        dist[v][u] = min(dist[v][u], d);
    }
    
    memset(visited, 0, sizeof(visited));
    int result = dfs(S, 1 << culture[S]);
    
    if (result == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}