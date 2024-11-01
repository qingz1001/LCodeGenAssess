#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    int next;
};

Edge edges[MAXN * 2];
int head[MAXN];
int edgeCount;
ll dist[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, ll w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dijkstra(int start) {
    for (int i = 0; i < MAXN; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[start] = 0;
    int current = start;
    for (int i = 0; i < MAXN; i++) {
        visited[current] = true;
        for (int j = head[current]; j != -1; j = edges[j].next) {
            int neighbor = edges[j].to;
            ll weight = edges[j].weight;
            if (!visited[neighbor] && dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
            }
        }
        ll minDist = INF;
        for (int i = 0; i < MAXN; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                current = i;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    edgeCount = 0;
    for (int i = 0; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    ll maxDist = 0;
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        for (int j = 1; j <= n; j++) {
            if (dist[j] > maxDist) {
                maxDist = dist[j];
            }
        }
    }

    printf("%.1lf\n", (double)maxDist / 2.0);
    return 0;
}