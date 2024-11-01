#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOD 64123

typedef struct {
    int x, y;
} Edge;

typedef struct {
    int *data;
    int size;
} List;

List createList(int size) {
    List list;
    list.data = (int *)malloc(size * sizeof(int));
    list.size = size;
    return list;
}

void destroyList(List list) {
    free(list.data);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int dfs(int node, int parent, int **adj, int *danger, int n, int k) {
    int *subtree = (int *)malloc((n + 1) * sizeof(int));
    int subtreeSize = 0;

    for (int i = 1; i <= n; i++) {
        if (adj[node][i] && i != parent) {
            subtree[subtreeSize++] = dfs(i, node, adj, danger, n, k);
        }
    }

    subtree[subtreeSize++] = danger[node];
    qsort(subtree, subtreeSize, sizeof(int), compare);

    int result = 0;
    if (subtreeSize >= k) {
        result = subtree[subtreeSize - k];
    }

    free(subtree);
    return result;
}

int main() {
    int n, k, W;
    scanf("%d %d %d", &n, &k, &W);

    int *danger = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &danger[i]);
    }

    Edge *edges = (Edge *)malloc((n - 1) * sizeof(Edge));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &edges[i].x, &edges[i].y);
    }

    int **adj = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 1; i <= n; i++) {
        adj[i] = (int *)calloc(n + 1, sizeof(int));
    }

    for (int i = 0; i < n - 1; i++) {
        adj[edges[i].x][edges[i].y] = 1;
        adj[edges[i].y][edges[i].x] = 1;
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += dfs(i, -1, adj, danger, n, k);
        result %= MOD;
    }

    printf("%d\n", result);

    for (int i = 1; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(edges);
    free(danger);

    return 0;
}