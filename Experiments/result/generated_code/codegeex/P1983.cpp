#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int n, m;
int in[MAXN], out[MAXN], stack[MAXN], top;
int degree[MAXN], level[MAXN];

void dfs(int u) {
    in[u] = 1;
    stack[++top] = u;
    for (int v = u + 1; v <= n; v++) {
        if (in[v]) continue;
        if (!degree[v]) {
            level[v] = level[u];
            dfs(v);
        } else {
            level[v] = level[u] + 1;
            dfs(v);
        }
    }
    out[u] = 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int s, x;
        scanf("%d", &s);
        for (int j = 0; j < s; j++) {
            scanf("%d", &x);
            degree[x] = 1;
        }
    }

    int maxLevel = 0;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            level[i] = 1;
            dfs(i);
        }
        maxLevel = (maxLevel > level[i]) ? maxLevel : level[i];
    }

    printf("%d\n", maxLevel);
    return 0;
}