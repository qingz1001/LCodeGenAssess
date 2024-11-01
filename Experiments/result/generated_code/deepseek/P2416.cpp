#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 300005

typedef struct {
    int to, hasPuff;
} Edge;

Edge edges[MAXN];
int head[MAXN], nextEdge[MAXN], edgeCount = 0;
bool visited[MAXN];

void addEdge(int u, int v, int hasPuff) {
    edges[edgeCount].to = v;
    edges[edgeCount].hasPuff = hasPuff;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
}

bool dfs(int u, int target) {
    if (u == target) return true;
    visited[u] = true;
    for (int i = head[u]; i != -1; i = nextEdge[i]) {
        int v = edges[i].to;
        if (!visited[v] && edges[i].hasPuff) {
            if (dfs(v, target)) return true;
        }
    }
    return false;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N; i++) head[i] = -1;
    
    for (int i = 0; i < M; i++) {
        int X, Y, Z;
        scanf("%d %d %d", &X, &Y, &Z);
        addEdge(X, Y, Z);
        addEdge(Y, X, Z);
    }
    
    int Q;
    scanf("%d", &Q);
    
    while (Q--) {
        int S, T;
        scanf("%d %d", &S, &T);
        
        for (int i = 1; i <= N; i++) visited[i] = false;
        
        if (dfs(S, T)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}