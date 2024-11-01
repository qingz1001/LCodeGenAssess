#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 100001

struct Edge {
    int to;
    int weight;
    struct Edge *next;
};

int n, m;
int dist[MAXN];
struct Edge *head[MAXN];

void addEdge(int u, int v, int w) {
    struct Edge *newEdge = (struct Edge *)malloc(sizeof(struct Edge));
    newEdge->to = v;
    newEdge->weight = w;
    newEdge->next = head[u];
    head[u] = newEdge;
}

void dfs(int u, int parent) {
    for (struct Edge *e = head[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v != parent) {
            dist[v] = dist[u] + e->weight;
            dfs(v, u);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    // Calculate the distance from node 1 to all other nodes
    dist[1] = 0;
    dfs(1, -1);

    int totalDistance = 0;
    for (int i = 2; i <= n; i++) {
        totalDistance += 2 * dist[i];
    }

    printf("%d\n", totalDistance);

    return 0;
}