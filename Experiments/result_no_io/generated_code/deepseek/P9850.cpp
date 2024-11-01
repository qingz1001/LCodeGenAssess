#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int u, v;
} Edge;

Edge redEdges[MAXM];
int blueDegree[MAXN] = {0};

int compareEdges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    if (edgeA->u == edgeB->u) return edgeA->v - edgeB->v;
    return edgeA->u - edgeB->u;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &redEdges[i].u, &redEdges[i].v);
        blueDegree[redEdges[i].u]++;
        blueDegree[redEdges[i].v]++;
    }

    qsort(redEdges, m, sizeof(Edge), compareEdges);

    long long redKeys = 0, blueKeys = 0;

    for (int i = 0; i < m; i++) {
        int u = redEdges[i].u;
        int v = redEdges[i].v;
        blueKeys += (long long)blueDegree[u] * blueDegree[v];
    }

    for (int i = 0; i < n; i++) {
        blueKeys += (long long)blueDegree[i] * (blueDegree[i] - 1) / 2;
    }

    redKeys = (long long)m * (m - 1) / 2 - blueKeys;

    printf("%lld\n", abs(redKeys - blueKeys));

    return 0;
}