#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXM 600005

struct Edge {
    int to, next, weight;
} edges[MAXM];

int head[MAXN], dist[MAXN], n, m, s, maxDist, minMaxDist;
int *queue, front, rear;

void addEdge(int u, int v, int w) {
    edges[m].to = v;
    edges[m].weight = w;
    edges[m].next = head[u];
    head[u] = m++;
}

void bfs(int start) {
    int u, v, w;
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    queue[front++] = start;
    while (front != rear) {
        u = queue[rear++];
        if (rear == MAXN) rear = 0;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            v = edges[i].to;
            w = edges[i].weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                queue[front++] = v;
                if (front == MAXN) front = 0;
            }
        }
    }
}

int main() {
    int u, v, w;
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    queue = (int *)malloc(sizeof(int) * n);
    front = rear = 0;
    maxDist = 0;
    for (int i = 1; i <= n; i++) {
        bfs(i);
        for (int j = 1; j <= n; j++) {
            if (dist[j] <= s) {
                maxDist = maxDist > dist[j] ? maxDist : dist[j];
            }
        }
        if (maxDist < minMaxDist || i == 1) {
            minMaxDist = maxDist;
        }
        maxDist = 0;
    }
    printf("%d\n", minMaxDist);
    free(queue);
    return 0;
}