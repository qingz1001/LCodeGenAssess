#include <stdio.h>
#include <stdlib.h>

#define MAXN 2001

typedef struct Edge {
    int v;
    struct Edge *next;
} Edge;

int n, m;
int k[MAXN];
Edge *g[MAXN];

void addEdge(int u, int v) {
    Edge *e = (Edge*)malloc(sizeof(Edge));
    e->v = v;
    e->next = g[u];
    g[u] = e;
}

int topoSort() {
    int inDegree[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        for (Edge *e = g[i]; e; e = e->next) {
            inDegree[e->v]++;
        }
    }

    int *queue = (int*)malloc((n+1) * sizeof(int));
    int front = 1, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            queue[++rear] = i;
        }
    }

    int count = 0;
    int *topoOrder = (int*)malloc((n+1) * sizeof(int));
    while (front <= rear) {
        int u = queue[front++];
        topoOrder[++count] = u;
        for (Edge *e = g[u]; e; e = e->next) {
            if (--inDegree[e->v] == 0) {
                queue[++rear] = e->v;
            }
        }
    }

    free(queue);
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
        g[i] = NULL;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int *topoOrder = (int*)malloc((n+1) * sizeof(int));
    int count = topoSort();
    for (int i = 1; i <= count; i++) {
        printf("%d ", topoOrder[i]);
    }
    printf("\n");

    int *minIndex = (int*)malloc((n+1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        minIndex[i] = 0;
    }
    for (int i = 1; i <= count; i++) {
        int u = topoOrder[i];
        minIndex[u] = i;
        for (Edge *e = g[u]; e; e = e->next) {
            minIndex[e->v] = min(minIndex[e->v], minIndex[u]);
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", minIndex[i]);
    }
    printf("\n");

    free(topoOrder);
    free(minIndex);
    for (int i = 1; i <= n; i++) {
        Edge *e = g[i];
        while (e) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}