#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int from, to, cap, flow, cost;
} Edge;

Edge edges[10000];
int head[10000], next[10000], edgeCount = 0;
int dist[10000], parent[10000], inQueue[10000];
int source, sink, nVertices;

void addEdge(int from, int to, int cap, int cost) {
    edges[edgeCount] = (Edge){from, to, cap, 0, cost};
    next[edgeCount] = head[from];
    head[from] = edgeCount++;
    edges[edgeCount] = (Edge){to, from, 0, 0, -cost};
    next[edgeCount] = head[to];
    head[to] = edgeCount++;
}

int dijkstra() {
    int i, u, v, minCost = 0;
    for (i = 0; i < nVertices; i++) {
        dist[i] = 1000000000;
        inQueue[i] = 0;
    }
    dist[source] = 0;
    inQueue[source] = 1;
    parent[source] = -1;
    while (1) {
        u = -1;
        for (i = 0; i < nVertices; i++) {
            if (inQueue[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (u == -1 || u == sink) break;
        inQueue[u] = 0;
        for (i = head[u]; i != -1; i = next[i]) {
            v = edges[i].to;
            if (edges[i].cap > edges[i].flow && dist[u] + edges[i].cost < dist[v]) {
                dist[v] = dist[u] + edges[i].cost;
                parent[v] = i;
            }
        }
    }
    if (dist[sink] == 1000000000) return -1;
    int flow = 1000000000;
    for (u = sink; u != source; u = edges[parent[u] ^ 1].to) {
        flow = flow < edges[parent[u]].cap - edges[parent[u]].flow ? flow : edges[parent[u]].cap - edges[parent[u]].flow;
    }
    for (u = sink; u != source; u = edges[parent[u] ^ 1].to) {
        edges[parent[u]].flow += flow;
        edges[parent[u] ^ 1].flow -= flow;
        minCost += flow * edges[parent[u]].cost;
    }
    return minCost;
}

int main() {
    int i, j, n, p, m, f, n, s, r[2001], cost = 0;
    scanf("%d", &n);
    nVertices = n * 2 + 2;
    source = 0;
    sink = n * 2 + 1;
    for (i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }
    scanf("%d %d %d %d %d", &p, &m, &f, &n, &s);
    for (i = 1; i <= n; i++) {
        addEdge(source, i, r[i], 0);
        addEdge(i + n, sink, r[i], 0);
        addEdge(source, i + n, 1000000000, p);
        addEdge(i, i + n, 1000000000, 0);
        if (i + m <= n) addEdge(i, i + m + n, 1000000000, f);
        if (i + n - m >= 1) addEdge(i + n, i + n - m, 1000000000, f);
        if (i + n - n >= 1) addEdge(i + n, i + n - n, 1000000000, s);
        if (i + n + m <= n) addEdge(i + n, i + n + m, 1000000000, s);
    }
    for (i = 0; i < nVertices; i++) {
        head[i] = -1;
    }
    while (1) {
        int minCost = dijkstra();
        if (minCost == -1) break;
        cost += minCost;
    }
    printf("%d\n", cost);
    return 0;
}