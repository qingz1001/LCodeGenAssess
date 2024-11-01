#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005
#define MAX_M 500005

struct Edge {
    int to, next, weight;
} edge[MAX_M * 2];

int head[MAX_N], cnt;
int n, s, max_depth, total_depth;
int depth[MAX_N];

void add_edge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].weight = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int parent, int d) {
    depth[u] = d;
    if (d > max_depth) max_depth = d;
    total_depth += d;
    
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v != parent) {
            dfs(v, u, d + edge[i].weight);
        }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &s);
    
    memset(head, -1, sizeof(head));
    
    for (int i = 0; i < n - 1; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    
    dfs(s, -1, 0);
    
    int result = max_depth * (n - 1) - total_depth;
    printf("%d\n", result);
    
    return 0;
}