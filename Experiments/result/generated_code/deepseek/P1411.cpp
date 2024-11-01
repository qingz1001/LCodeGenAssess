#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 701

typedef struct {
    int v;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int size[MAXN];
int n;

void addEdge(int u, int v) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->v = v;
    e->next = graph[u];
    graph[u] = e;
}

int dfs(int u, int parent) {
    size[u] = 1;
    for (Edge *e = graph[u]; e != NULL; e = e->next) {
        if (e->v != parent) {
            size[u] += dfs(e->v, u);
        }
    }
    return size[u];
}

long long maxScore(int u, int parent) {
    long long maxProduct = 0;
    int totalSize = size[u];

    for (Edge *e = graph[u]; e != NULL; e = e->next) {
        if (e->v != parent) {
            long long product = (long long)(totalSize - size[e->v]) * size[e->v];
            maxProduct = maxProduct > product ? maxProduct : product;
            long long childProduct = maxScore(e->v, u);
            maxProduct = maxProduct > childProduct ? maxProduct : childProduct;
        }
    }

    return maxProduct;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    dfs(1, -1);
    long long result = maxScore(1, -1);
    printf("%lld\n", result);

    for (int i = 1; i <= n; i++) {
        Edge *e = graph[i];
        while (e != NULL) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}