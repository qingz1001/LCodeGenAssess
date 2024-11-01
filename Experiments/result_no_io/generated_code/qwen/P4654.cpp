#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, t, m;
int parent[MAXN];
int depth[MAXN];
int child[MAXN][2];

void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = (p == -1 ? 0 : depth[p] + 1);
    for (int i = 0; i < 2; ++i) {
        if (child[u][i]) {
            dfs(child[u][i], u);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i <= n; ++i) {
        parent[i] = -1;
        depth[i] = 0;
        child[i][0] = child[i][1] = 0;
    }

    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (!child[a][0]) child[a][0] = b;
        else child[a][1] = b;
        if (!child[b][0]) child[b][0] = a;
        else child[b][1] = a;
    }

    dfs(t, -1);

    int max_depth = 0;
    for (int i = 1; i <= n; ++i) {
        max_depth = (depth[i] > max_depth ? depth[i] : max_depth);
    }

    printf("%d\n", max_depth / 2 + (max_depth % 2));

    return 0;
}