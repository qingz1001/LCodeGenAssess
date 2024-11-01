#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 200005
#define MAXM 200005
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to, next;
    ll weight;
} edges[MAXM];

int head[MAXN], edgeCount;
ll dist[MAXN], minCost[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, ll w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dijkstra(int start) {
    memset(visited, false, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));
    memset(minCost, 0x3f, sizeof(minCost));
    dist[start] = 0;
    minCost[start] = 0;

    for (int i = 1; i < MAXN; i++) {
        int u = -1;
        for (int j = 1; j < MAXN; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = true;

        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            ll weight = edges[j].weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                minCost[v] = minCost[u] + weight * dist[v] + dist[v] * dist[v];
            } else if (dist[u] + weight == dist[v]) {
                minCost[v] = min(minCost[v], minCost[u] + weight * dist[v] + dist[v] * dist[v]);
            }
        }
    }
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    memset(head, -1, sizeof(head));
    edgeCount = 0;

    for (int i = 2; i <= n; i++) {
        int f, s;
        ll p, q, l;
        scanf("%d %lld %lld %lld %lld", &f, &s, &p, &q, &l);
        addEdge(f, i, s);
    }

    dijkstra(1);

    for (int i = 2; i <= n; i++) {
        printf("%lld\n", minCost[i]);
    }

    return 0;
}