#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005

typedef struct Edge {
    int to, len;
    struct Edge *next;
} Edge;

Edge *head[MAXN];
int n, s;
int dist[MAXN], max_dist;

void add_edge(int u, int v, int w) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v;
    e->len = w;
    e->next = head[u];
    head[u] = e;
}

void dfs(int u, int parent) {
    for (Edge *e = head[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        dist[v] = dist[u] + e->len;
        if (dist[v] > max_dist) max_dist = dist[v];
        dfs(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    max_dist = 0;
    dist[1] = 0;
    dfs(1, -1);

    int max_node = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == max_dist) {
            max_node = i;
            break;
        }
    }

    max_dist = 0;
    dist[max_node] = 0;
    dfs(max_node, -1);

    int diameter = max_dist;
    int ans = INT_MAX;

    for (int i = 1; i <= n; i++) {
        if (dist[i] <= s) {
            int max_dist_to_path = 0;
            for (int j = 1; j <= n; j++) {
                int dist_to_path = dist[j] - dist[i];
                if (dist_to_path > max_dist_to_path) {
                    max_dist_to_path = dist_to_path;
                }
            }
            if (max_dist_to_path < ans) {
                ans = max_dist_to_path;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}