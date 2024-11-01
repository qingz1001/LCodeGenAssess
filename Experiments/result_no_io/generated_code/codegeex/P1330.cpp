#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 100005

int n, m;
int adj[MAXN][MAXN], visited[MAXN], color[MAXN];

void dfs(int node, int c) {
    visited[node] = 1;
    color[node] = c;
    for (int i = 1; i <= n; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(i, 3 - c); // Alternate colors
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    // Initialize
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    // Start DFS from node 1
    dfs(1, 1);

    int count1 = 0, count2 = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 1) count1++;
        else if (color[i] == 2) count2++;
    }

    printf("%d\n", (count1 < count2) ? count1 : count2);

    return 0;
}