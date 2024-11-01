#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 700

typedef struct {
    int v;
    struct Edge* next;
} Edge;

Edge* adj[MAXN + 1];
int size[MAXN + 1];
int n;

void addEdge(int u, int v) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v = v;
    e->next = adj[u];
    adj[u] = e;
}

void dfs(int u, int parent) {
    size[u] = 1;
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->v;
        if (v != parent) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

long long maxProduct(int u, int parent) {
    long long maxProd = 0;
    int totalSize = size[u];

    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->v;
        if (v != parent) {
            long long prod = (long long)(totalSize - size[v]) * size[v];
            if (prod > maxProd) {
                maxProd = prod;
            }
            long long childProd = maxProduct(v, u);
            if (childProd > maxProd) {
                maxProd = childProd;
            }
        }
    }

    return maxProd;
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
    long long result = maxProduct(1, -1);
    printf("%lld\n", result);

    for (int i = 1; i <= n; i++) {
        Edge* e = adj[i];
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}