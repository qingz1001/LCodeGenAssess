#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
    int to;
    long long length;
    struct Edge *next;
} Edge;

Edge *edges[50005];
int edgeCount[50005];
int dist[50005];
int inQueue[50005];
int visited[50005];
int pre[50005];
int next[50005];
int n, m, S, T;
long long totalLength;

void addEdge(int u, int v, long long w) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->to = v;
    newEdge->length = w;
    newEdge->next = edges[u];
    edges[u] = newEdge;
    edgeCount[u]++;
}

void spfa(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(inQueue, 0, sizeof(inQueue));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;
    visited[start] = 1;
    inQueue[start] = 1;
    pre[start] = -1;
    next[start] = -1;

    while (1) {
        int u = -1;
        long long minDist = 0x3f3f3f3f3f3f3f3fLL;
        for (int i = 1; i <= n; i++) {
            if (!inQueue[i] && dist[i] < minDist) {
                u = i;
                minDist = dist[i];
            }
        }
        if (u == -1) break;
        inQueue[u] = 0;
        for (Edge *e = edges[u]; e != NULL; e = e->next) {
            int v = e->to;
            long long w = e->length;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                next[v] = next[u];
                next[u] = v;
                if (!inQueue[v]) {
                    inQueue[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        totalLength += w;
    }

    spfa(S);
    int *queue = (int *)malloc(sizeof(int) * (n + 1));
    int front = 0, rear = 0;
    queue[rear++] = T;
    int count = 0;
    while (front < rear) {
        int u = queue[front++];
        for (Edge *e = edges[u]; e != NULL; e = e->next) {
            int v = e->to;
            if (dist[u] + e->length == dist[v] && v != pre[u]) {
                queue[rear++] = v;
            }
        }
    }

    spfa(T);
    memset(queue, 0, sizeof(queue));
    front = 0;
    rear = 0;
    queue[rear++] = S;
    while (front < rear) {
        int u = queue[front++];
        for (Edge *e = edges[u]; e != NULL; e = e->next) {
            int v = e->to;
            if (dist[u] + e->length == dist[v] && v != pre[u]) {
                queue[rear++] = v;
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (next[i] != -1 && pre[i] != -1) {
            int u = i, v = next[i];
            while (u != -1 && v != -1 && pre[u] != v) {
                u = pre[u];
                v = next[v];
            }
            if (u == -1 || v == -1) {
                ans += dist[i] + dist[next[i]] - 2 * dist[T];
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}