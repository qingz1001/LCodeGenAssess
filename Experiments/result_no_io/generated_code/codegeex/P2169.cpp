#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200001
#define MAXM 1000001

typedef struct {
    int to;
    int weight;
} Edge;

Edge edges[MAXM];
int head[MAXN];
int dist[MAXN];
int inDegree[MAXN];
int n, m;

void addEdge(int u, int v, int w) {
    static int edgeCount = 0;
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    head[u] = edgeCount++;
}

void topoSort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].to) {
            int v = edges[i].to;
            if (--inDegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
}

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    topoSort();
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (inDegree[j] == 0) {
                if (u == -1 || dist[u] > dist[j]) {
                    u = j;
                }
            }
        }
        if (u == -1) break;
        inDegree[u] = -1;
        for (int i = head[u]; i != -1; i = edges[i].to) {
            int v = edges[i].to;
            if (dist[u] + edges[i].weight < dist[v]) {
                dist[v] = dist[u] + edges[i].weight;
            }
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        inDegree[v]++;
    }
    dijkstra();
    printf("%d\n", dist[n]);
    return 0;
}