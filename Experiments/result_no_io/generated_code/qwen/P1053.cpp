#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

int n;
int adj[MAXN][2];
int visited[MAXN];

void dfs(int u, int *cycle, int *size) {
    if (visited[u]) return;
    visited[u] = 1;
    cycle[(*size)++] = u;
    dfs(adj[u][0], cycle, size);
    dfs(adj[u][1], cycle, size);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &adj[i][0], &adj[i][1]);
    }

    int total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int cycle[MAXN], size = 0;
            dfs(i, cycle, &size);

            int cost = -1;
            for (int j = 0; j < size; ++j) {
                if (cost == -1 || abs(cycle[j] - cycle[(j + 1) % size]) != 1 && abs(cycle[j] - cycle[(j + 1) % size]) != n - 1) {
                    cost = size;
                }
            }

            if (cost == -1) {
                printf("-1\n");
                return 0;
            }

            total_cost += cost;
        }
    }

    printf("%d\n", total_cost);
    return 0;
}