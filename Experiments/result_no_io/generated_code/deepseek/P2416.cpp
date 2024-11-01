#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 300005

typedef struct {
    int to, hasPuff;
} Edge;

typedef struct {
    Edge edges[MAXN];
    int head[MAXN], cnt;
} Graph;

Graph G;
bool visited[MAXN];
int parent[MAXN], hasPuff[MAXN];

void addEdge(int u, int v, int z) {
    G.edges[G.cnt].to = v;
    G.edges[G.cnt].hasPuff = z;
    G.edges[G.cnt].next = G.head[u];
    G.head[u] = G.cnt++;
}

void dfs(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    for (int i = G.head[u]; i != -1; i = G.edges[i].next) {
        int v = G.edges[i].to;
        if (!visited[v]) {
            hasPuff[v] = hasPuff[u] || G.edges[i].hasPuff;
            dfs(v, u);
        }
    }
}

bool canReachWithPuff(int s, int t) {
    if (s == t) return true;
    while (t != s) {
        if (hasPuff[t]) return true;
        t = parent[t];
    }
    return hasPuff[s];
}

int main() {
    int N, M, Q, X, Y, Z, S, T;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        G.head[i] = -1;
        visited[i] = false;
        hasPuff[i] = 0;
    }
    G.cnt = 0;

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &X, &Y, &Z);
        addEdge(X, Y, Z);
        addEdge(Y, X, Z);
    }

    dfs(1, -1);

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &S, &T);
        if (canReachWithPuff(S, T)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}