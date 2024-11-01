#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef struct Edge {
    int to, time, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int n, s;
long long max_time[MAXN], result = 0;

void add_edge(int u, int v, int t) {
    edges[edge_count].to = v;
    edges[edge_count].time = t;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int node, int parent) {
    max_time[node] = 0;
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == parent) continue;
        dfs(to, node);
        if (max_time[to] + edges[i].time > max_time[node]) {
            max_time[node] = max_time[to] + edges[i].time;
        }
    }
    for (int i = head[node]; i != -1; i = edges[i].next) {
        int to = edges[i].to;
        if (to == parent) continue;
        result += max_time[node] - (max_time[to] + edges[i].time);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 1; i < n; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }
    dfs(s, -1);
    printf("%lld\n", result);
    return 0;
}