#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 1000001
#define MAX_M 1000001
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next;
    ll cost;
} edge[MAX_M], edge_rev[MAX_M];

int head[MAX_N], head_rev[MAX_N], cnt, cnt_rev;
ll dist[MAX_N], dist_rev[MAX_N];
int vis[MAX_N];

void add_edge(int u, int v, ll w) {
    edge[cnt].to = v;
    edge[cnt].cost = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;

    edge_rev[cnt_rev].to = u;
    edge_rev[cnt_rev].cost = w;
    edge_rev[cnt_rev].next = head_rev[v];
    head_rev[v] = cnt_rev++;
}

void dijkstra(int s, ll *dist, struct Edge *e, int *h) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i < MAX_N; i++) dist[i] = INF;
    dist[s] = 0;

    for (int i = 1; i < MAX_N; i++) {
        int u = -1;
        ll min_dist = INF;
        for (int j = 1; j < MAX_N; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int j = h[u]; ~j; j = e[j].next) {
            int v = e[j].to;
            if (dist[v] > dist[u] + e[j].cost) {
                dist[v] = dist[u] + e[j].cost;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));
    memset(head_rev, -1, sizeof(head_rev));

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
    }

    dijkstra(1, dist, edge, head);
    dijkstra(1, dist_rev, edge_rev, head_rev);

    ll total_cost = 0;
    for (int i = 2; i <= n; i++) {
        total_cost += dist[i] + dist_rev[i];
    }

    printf("%lld\n", total_cost);

    return 0;
}