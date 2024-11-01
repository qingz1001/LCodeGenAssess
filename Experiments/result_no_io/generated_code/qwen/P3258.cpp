#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int n;
int a[MAXN];
int parent[MAXN];
int size[MAXN];

void dfs(int u, int p) {
    parent[u] = p;
    size[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (v != u && v != p && parent[v] == -1) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }

    dfs(1, -1);

    int ans[MAXN];
    for (int i = 1; i <= n; i++) {
        ans[i] = 0;
    }

    for (int i = n; i >= 1; i--) {
        if (parent[a[i]] != -1) {
            ans[parent[a[i]]] += ans[a[i]] + 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}