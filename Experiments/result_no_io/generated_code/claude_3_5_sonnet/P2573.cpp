#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 1000005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next;
    ll weight;
} edges[MAX_M * 2];

int head[MAX_N], cnt;
int h[MAX_N], n, m;
int order[MAX_N], idx;
ll dist[MAX_N];
int vis[MAX_N];

void add_edge(int u, int v, ll w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int cmp(const void *a, const void *b) {
    return h[*(int*)b] - h[*(int*)a];
}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            if (dist[v] > dist[u] + edges[e].weight) {
                dist[v] = dist[u] + edges[e].weight;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        order[i] = i;
    }

    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    qsort(order + 1, n, sizeof(int), cmp);

    int max_count = 0;
    ll min_dist = 0;

    dijkstra(1);

    for (int i = 1; i <= n; i++) {
        int u = order[i];
        if (dist[u] != INF) {
            max_count++;
            if (dist[u] > min_dist) {
                min_dist = dist[u];
            }
        }
    }

    printf("%d %lld\n", max_count, min_dist);

    return 0;
}