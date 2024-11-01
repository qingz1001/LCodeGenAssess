#include <stdio.h>
#include <stdlib.h>

#define MOD 64123

int n, k, W;
int *d;
int **graph;
int *parent;

void dfs(int node, int prev) {
    parent[node] = prev;
    for (int i = 0; i < graph[node][0]; ++i) {
        int neighbor = graph[node][i + 1];
        if (neighbor != prev) {
            dfs(neighbor, node);
        }
    }
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int main() {
    scanf("%d %d %d", &n, &k, &W);
    d = (int *)malloc((n + 1) * sizeof(int));
    graph = (int **)malloc((n + 1) * sizeof(int *));
    parent = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &d[i]);
        graph[i] = (int *)malloc((n + 2) * sizeof(int));
        graph[i][0] = 0;
        parent[i] = i;
    }

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][++graph[x][0]] = y;
        graph[y][++graph[y][0]] = x;
    }

    dfs(1, 0);

    long long sum = 0;
    for (int s = k; s <= n; ++s) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (cnt >= s) break;
            if (find(i) == i && d[i] >= d[find(graph[i][1])]) {
                ++cnt;
                sum += d[i];
                sum %= MOD;
            }
        }
    }

    printf("%lld\n", sum);

    free(d);
    for (int i = 1; i <= n; ++i) {
        free(graph[i]);
    }
    free(graph);
    free(parent);

    return 0;
}