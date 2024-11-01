#include <stdio.h>
#include <stdlib.h>

#define MAXN 500001

int n, visited[MAXN], dist[MAXN], parent[MAXN], path[MAXN];
int *edges[MAXN], *edges_count;

void dfs(int node) {
    visited[node] = 1;
    for (int i = 0; i < edges_count[node]; i++) {
        int neighbor = edges[node][i];
        if (!visited[neighbor]) {
            parent[neighbor] = node;
            dist[neighbor] = dist[node] + 1;
            dfs(neighbor);
        }
    }
}

void find_path(int node) {
    path[node] = 1;
    if (node == n) {
        return;
    }
    for (int i = 0; i < edges_count[node]; i++) {
        int neighbor = edges[node][i];
        if (dist[neighbor] == dist[node] + 1 && !path[neighbor]) {
            find_path(neighbor);
            break;
        }
    }
}

int main() {
    scanf("%d", &n);
    edges_count = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        edges[i] = (int *)calloc(MAXN, sizeof(int));
    }

    int a, b;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        edges[a][edges_count[a]++] = b;
        edges[b][edges_count[b]++] = a;
    }

    dfs(1);
    find_path(n);

    if (!path[1]) {
        printf("BRAK\n");
    } else {
        for (int i = 1; i <= n; i++) {
            if (path[i]) {
                printf("%d\n", i);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        free(edges[i]);
    }
    free(edges_count);

    return 0;
}