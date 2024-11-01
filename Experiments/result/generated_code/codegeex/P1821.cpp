#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
using namespace std;

#define MAXN 1001
#define MAXM 100001

struct Edge {
    int to, next, weight;
};

Edge edges[MAXM * 2];
int head[MAXN], dist[MAXN], n, m, x, edgeCount;

void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + MAXN, INT_MAX);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra(x);

    int maxDistance = 0;
    for (int i = 1; i <= n; i++) {
        maxDistance = max(maxDistance, dist[i]);
    }

    dijkstra(x);

    for (int i = 1; i <= n; i++) {
        maxDistance = max(maxDistance, dist[i]);
    }

    printf("%d\n", maxDistance);
    return 0;
}