#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1001
#define MAXM 100001

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], dist[MAXN], queue[MAXN], inQueue[MAXN];
int n, m, edgeCount;

void addEdge(int u, int v, int w) {
    edges[edgeCount].v = v;
    edges[edgeCount].w = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void spfa(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        inQueue[i] = 0;
    }
    dist[start] = 0;
    int front = 0, rear = 0;
    queue[rear++] = start;
    inQueue[start] = 1;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN) front = 0;
        inQueue[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    queue[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    inQueue[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;
    edgeCount = 0;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    spfa(1);
    int totalTime = 0;
    for (int i = 2; i <= n; i++) {
        totalTime += dist[i];
    }

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edgeCount = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].v;
        int v = edges[i].u;
        int w = edges[i].w;
        addEdge(u, v, w);
    }

    spfa(1);
    for (int i = 2; i <= n; i++) {
        totalTime += dist[i];
    }

    printf("%d\n", totalTime);
    return 0;
}