#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 50005
#define MAXM 50005

typedef struct Edge {
    int to;
    int weight;
} Edge;

Edge graph[MAXM * 2];
int head[MAXN];
int edgeCount;
int dist[MAXN];
int inQueue[MAXN];
int prev[MAXN];
int next[MAXN];
bool inSP[MAXN];
bool inSSP[MAXN];
int queueHead;
int queueTail;

void addEdge(int u, int v, int w) {
    graph[edgeCount].to = v;
    graph[edgeCount].weight = w;
    head[u] = edgeCount++;
}

void initialize() {
    memset(head, -1, sizeof(head));
    edgeCount = 0;
}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(inQueue, 0, sizeof(inQueue));
    memset(prev, -1, sizeof(prev));
    memset(next, -1, sizeof(next));
    memset(inSP, 0, sizeof(inSP));
    memset(inSSP, 0, sizeof(inSSP));
    dist[start] = 0;
    inQueue[start] = 1;
    queueHead = queueTail = start;

    while (queueHead != -1) {
        int u = queueHead;
        inQueue[u] = 0;
        queueHead = next[u];
        if (queueHead != -1) {
            prev[queueHead] = -1;
        }

        for (int i = head[u]; i != -1; i = graph[i].to) {
            int v = graph[i].to;
            int w = graph[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    next[v] = queueTail;
                    prev[v] = queueHead;
                    queueTail = v;
                    inQueue[v] = 1;
                }
            }
        }
    }
}

int main() {
    int n, m, S, T;
    scanf("%d%d%d%d", &n, &m, &S, &T);
    initialize();

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dijkstra(S);
    int d = dist[T];

    dijkstra(T);
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (dist[i] == d && dist[T] == dist[i] + dist[S]) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}