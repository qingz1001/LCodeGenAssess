#include <stdio.h>
#include <limits.h>

#define MAXN 100

int minKey(int key[], int mstSet[], int N) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < N; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int primMST(int graph[MAXN][MAXN], int N) {
    int parent[MAXN];
    int key[MAXN];
    int mstSet[MAXN];

    for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < N - 1; count++) {
        int u = minKey(key, mstSet, N);
        mstSet[u] = 1;

        for (int v = 0; v < N; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int minCost = 0;
    for (int i = 1; i < N; i++)
        minCost += graph[i][parent[i]];

    return minCost;
}

int main() {
    int N;
    scanf("%d", &N);

    int graph[MAXN][MAXN];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &graph[i][j]);

    printf("%d\n", primMST(graph, N));

    return 0;
}