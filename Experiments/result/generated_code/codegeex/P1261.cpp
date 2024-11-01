#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 30010
#define MAXM 150010

struct Edge {
    int to, next, weight;
} edges[MAXM];

int head[MAXN], dist[MAXN], rank[MAXN], in_degree[MAXN], n, m, cnt, ans;
bool visited[MAXN];

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;
    for (int i = 1; i <= n; i++) {
        int min_dist = INT_MAX, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            if (dist[u] + edges[j].weight < dist[v]) {
                dist[v] = dist[u] + edges[j].weight;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &rank[i]);
        in_degree[rank[i]]++;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    for (int i = 10; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (rank[j] == i) {
                dijkstra(j);
                for (int k = 1; k <= n; k++) {
                    if (dist[k] != INT_MAX) {
                        if (rank[k] < i) {
                            ans += in_degree[rank[k]];
                            in_degree[rank[k]] = 0;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}