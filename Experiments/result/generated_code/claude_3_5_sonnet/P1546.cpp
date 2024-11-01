#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

int n;
int graph[MAX_N][MAX_N];
int parent[MAX_N];
int key[MAX_N];
int mstSet[MAX_N];

int minKey() {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int primMST() {
    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey();
        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int total_weight = 0;
    for (int i = 1; i < n; i++)
        total_weight += graph[i][parent[i]];

    return total_weight;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int result = primMST();
    printf("%d\n", result);

    return 0;
}