#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

int n, edges[MAXN][MAXN], size[MAXN], parent[MAXN];

void dfs(int u, int p) {
    size[u] = 1;
    for (int v = 0; v < n; v++) {
        if (edges[u][v] && v != p) {
            parent[v] = u;
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

double solve(int u, int p) {
    double total_time = size[u];
    if (size[u] == 1) return total_time;
    for (int v = 0; v < n; v++) {
        if (edges[u][v] && v != p) {
            total_time += solve(v, u);
        }
    }
    return total_time;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a][b] = edges[b][a] = 1;
    }

    dfs(0, -1);

    double expected_time = 0;
    for (int i = 0; i < n; i++) {
        expected_time += solve(i, -1);
    }

    printf("%.4f\n", expected_time / n);

    return 0;
}