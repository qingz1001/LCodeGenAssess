#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 50005

int n, m;
int adj[MAXN][MAXN];
int degree[MAXN];
int visited[MAXN];

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        adj[a][b] = 1;
        if (t == 2) {
            adj[b][a] = 1;
        }
        degree[a]++;
        degree[b]++;
    }

    int max_size = 0;
    int max_nodes[MAXM];
    int max_count = 0;

    for (int start = 1; start <= n; start++) {
        int size = 0;
        int nodes[MAXM];
        int count = 0;
        for (int i = 1; i <= n; i++) {
            visited[i] = 0;
        }
        dfs(start);
        for (int i = 1; i <= n; i++) {
            if (visited[i]) {
                nodes[count++] = i;
                size++;
            }
        }
        if (size > max_size || (size == max_size && count < max_count)) {
            max_size = size;
            max_count = count;
            for (int j = 0; j < count; j++) {
                max_nodes[j] = nodes[j];
            }
        }
    }

    printf("%d\n", max_size);
    for (int i = 0; i < max_count; i++) {
        printf("%d ", max_nodes[i]);
    }
    printf("\n");

    return 0;
}