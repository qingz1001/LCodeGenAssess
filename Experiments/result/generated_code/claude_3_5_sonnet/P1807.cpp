#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1505
#define MAX_M 50005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int dist[MAX_N];
int indegree[MAX_N];
int queue[MAX_N];

void addEdge(int from, int to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from];
    graph[from] = newEdge;
    indegree[to]++;
}

int topologicalSort(int n) {
    int front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        for (Edge* e = graph[u]; e; e = e->next) {
            int v = e->to;
            if (dist[u] + e->weight > dist[v]) {
                dist[v] = dist[u] + e->weight;
            }
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    return rear == n;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(graph, 0, sizeof(graph));
    memset(indegree, 0, sizeof(indegree));
    memset(dist, 0, sizeof(dist));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    if (topologicalSort(n) && dist[n] != 0) {
        printf("%d\n", dist[n]);
    } else {
        printf("-1\n");
    }

    return 0;
}