#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005
#define MAX_M 1000005

struct Edge {
    int to, next, w;
} edge[MAX_M];

int head[MAX_N], cnt;
int n, s, max_dist, min_dist = 1e9;
int dist[MAX_N];

void add_edge(int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa, int d) {
    dist[u] = d;
    if (head[u] == 0) {
        if (d > max_dist) max_dist = d;
        if (d < min_dist) min_dist = d;
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u, d + edge[i].w);
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &s);
    
    for (int i = 1; i < n; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    
    dfs(s, 0, 0);
    
    printf("%d\n", max_dist - min_dist);
    
    return 0;
}