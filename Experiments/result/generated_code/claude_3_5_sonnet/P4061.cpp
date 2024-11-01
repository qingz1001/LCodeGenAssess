#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 50005
#define MAX_M 50005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next, weight;
} edges[MAX_M * 2];

int head[MAX_N], cnt;
int dist[MAX_N], dist_rev[MAX_N];
bool vis[MAX_N];
int n, m, S, T;

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start, int *dist) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = true;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(S, dist);
    dijkstra(T, dist_rev);

    ll result = 0;
    for (int i = 1; i <= n; i++) {
        if (i == S || i == T) continue;
        for (int j = i + 1; j <= n; j++) {
            if (j == S || j == T) continue;
            if (dist[i] + dist_rev[j] == dist[T] && dist[j] + dist_rev[i] == dist[T] &&
                dist[i] + dist_rev[i] > dist[T] && dist[j] + dist_rev[j] > dist[T]) {
                result++;
            }
        }
    }

    printf("%lld\n", result);
    return 0;
}