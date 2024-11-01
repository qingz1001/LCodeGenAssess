#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define MAX_M 1000001
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Edge {
    int to, next;
    ll weight;
} edges[MAX_M * 2];

int head[MAX_N], cnt;
ll dist[MAX_N];
int vis[MAX_N];

void add_edge(int u, int v, ll w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = 0;
    }
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        ll min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            ll w = edges[e].weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(n);

    ll total_cost = 0;
    for (int i = 2; i <= n; i++) {
        total_cost += dist[i];
    }

    printf("%lld\n", total_cost * 2);

    return 0;
}