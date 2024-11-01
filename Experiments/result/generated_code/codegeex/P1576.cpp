#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2001
#define MAXM 100001

struct Edge {
    int to;
    int weight;
    struct Edge *next;
};

struct Edge *edges[MAXM];
int dist[MAXN];
bool visited[MAXN];

void addEdge(int u, int v, int w) {
    struct Edge *newEdge = (struct Edge *)malloc(sizeof(struct Edge));
    newEdge->to = v;
    newEdge->weight = w;
    newEdge->next = edges[u];
    edges[u] = newEdge;
}

void dijkstra(int start, int n) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = true;

        struct Edge *edge = edges[u];
        while (edge != NULL) {
            int v = edge->to;
            int w = edge->weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
            edge = edge->next;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        addEdge(x, y, z);
        addEdge(y, x, z);
    }

    int A, B;
    scanf("%d %d", &A, &B);

    dijkstra(A, n);

    double result = 100.0 * (1.0 + (double)dist[B] / 100.0);
    printf("%.8lf\n", result);

    return 0;
}