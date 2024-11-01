#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to;
    ll weight;
};

int n;
struct Edge graph[MAXN * 2];
int head[MAXN], next[MAXN * 2], edgeCount;
ll dist[MAXN], maxDist[MAXN];
int parent[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, ll w) {
    graph[edgeCount].to = v;
    graph[edgeCount].weight = w;
    next[edgeCount] = head[u];
    head[u] = edgeCount++;
}

void dfs(int u, ll d) {
    if (d > maxDist[u]) {
        maxDist[u] = d;
        parent[u] = v;
    }
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = graph[i].to;
        if (!visited[v]) {
            visited[v] = true;
            dfs(v, d + graph[i].weight);
        }
    }
}

void findCentroid(int u) {
    visited[u] = true;
    int size = 0;
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = graph[i].to;
        if (!visited[v]) {
            findCentroid(v);
            size++;
        }
    }
    if (size == 0) {
        parent[u] = u;
    }
}

int findLCA(int u, int v) {
    while (parent[u] != parent[v]) {
        if (dist[parent[u]] < dist[parent[v]]) {
            v = parent[v];
        } else {
            u = parent[u];
        }
    }
    return dist[u] < dist[v] ? u : v;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addEdge(u - 1, v - 1, w);
        addEdge(v - 1, u - 1, w);
    }

    visited[0] = true;
    dfs(0, 0);

    int centroid = 0;
    for (int i = 1; i < n; i++) {
        if (maxDist[i] > maxDist[centroid]) {
            centroid = i;
        }
    }

    findCentroid(centroid);

    for (int i = 0; i < n; i++) {
        dist[i] = maxDist[i];
    }

    for (int i = 0; i < n; i++) {
        int u = i;
        while (parent[u] != u) {
            int v = parent[u];
            int lca = findLCA(u, v);
            dist[u] = (dist[u] + dist[v] - 2 * dist[lca] + graph[head[u]].weight + graph[head[v]].weight) / 2;
            u = v;
        }
    }

    double result = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > result) {
            result = dist[i];
        }
    }

    printf("%.1f\n", result / 2.0);

    return 0;
}