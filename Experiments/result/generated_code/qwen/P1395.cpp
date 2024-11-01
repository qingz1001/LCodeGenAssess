#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001

int n;
int graph[MAXN][MAXN];
int size[MAXN];

void dfs(int u, int parent) {
    size[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && v != parent) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

int centroid(int u, int parent, int total_size) {
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && v != parent && size[v] * 2 > total_size) {
            return centroid(v, u, total_size);
        }
    }
    return u;
}

void calculate_distances(int u, int parent, int distance, int *sum) {
    *sum += distance * size[u];
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && v != parent) {
            calculate_distances(v, u, distance + 1, sum);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    int root = centroid(1, -1, n);
    int min_sum = INT_MAX;
    int best_node = -1;

    for (int i = 1; i <= n; i++) {
        int sum = 0;
        calculate_distances(i, -1, 0, &sum);
        if (sum < min_sum || (sum == min_sum && i < best_node)) {
            min_sum = sum;
            best_node = i;
        }
    }

    printf("%d %d\n", best_node, min_sum);

    return 0;
}