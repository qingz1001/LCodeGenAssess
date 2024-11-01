#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005

int n, m;
int k[MAXN];
int adj[MAXN][MAXN];
int in_degree[MAXN];
int result[MAXN];
int min_order[MAXN];

void topological_sort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }
    while (front < rear) {
        int u = queue[front++];
        result[u] = 1;
        for (int v = 1; v <= n; ++v) {
            if (adj[u][v]) {
                if (--in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }
}

void dfs(int u, int order) {
    min_order[u] = order;
    for (int v = 1; v <= n; ++v) {
        if (adj[u][v]) {
            dfs(v, order + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k[i]);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][b] = 1;
        in_degree[b]++;
    }
    topological_sort();
    for (int i = 1; i <= n; ++i) {
        if (!result[i]) {
            dfs(i, 1);
        }
    }
    printf("Feasible sequence: ");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    printf("Minimum orders: ");
    for (int i = 1; i <= n; ++i) {
        printf("%d ", min_order[i]);
    }
    printf("\n");
    return 0;
}