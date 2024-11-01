#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n;
int tree[MAXN][MAXN];
int visited[MAXN];

void dfs(int u, int depth) {
    if (visited[u]) return;
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (tree[u][v] && !visited[v]) {
            dfs(v, depth + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int a;
        scanf("%d", &a);
        tree[i][a] = 1;
        tree[a][i] = 1;
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}