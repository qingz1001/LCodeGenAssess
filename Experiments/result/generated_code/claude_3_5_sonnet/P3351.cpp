#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005

int n, m;
int parent[MAX_N], rank[MAX_N];
int adj[MAX_N][MAX_N];
int low[MAX_N], dfn[MAX_N], is_cut[MAX_N];
int timer = 0, answer = 0;

void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

void dfs(int u, int p) {
    int children = 0;
    low[u] = dfn[u] = ++timer;
    
    for (int v = 1; v <= n; v++) {
        if (adj[u][v]) {
            if (v == p) continue;
            if (dfn[v] == 0) {
                children++;
                dfs(v, u);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
                if ((p != 0 && low[v] >= dfn[u]) || (p == 0 && children > 1)) {
                    is_cut[u] = 1;
                }
            } else {
                low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    init();
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
        unite(u, v);
    }
    
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            dfs(i, 0);
        }
    }
    
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (find(u) != find(v)) continue;
            if (!is_cut[u] && !is_cut[v]) {
                answer++;
            } else if ((is_cut[u] && !is_cut[v]) || (!is_cut[u] && is_cut[v])) {
                int connected = 0;
                for (int w = 1; w <= n; w++) {
                    if (w == u || w == v) continue;
                    if (adj[u][w] && adj[v][w]) {
                        connected = 1;
                        break;
                    }
                }
                if (!connected) answer++;
            }
        }
    }
    
    printf("%d\n", answer);
    return 0;
}