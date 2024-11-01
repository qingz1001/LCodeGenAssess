#include <stdio.h>
#include <stdlib.h>

#define MAXN 500001

int n, m;
int g[MAXN][2], p[MAXN], d[MAXN], v[MAXN];

void dfs(int u) {
    v[u] = 1;
    if (d[u] == 1) {
        printf("%d\n", u);
        return;
    }
    int i;
    for (i = 0; i < d[u]; i++) {
        if (v[g[u][i]]) continue;
        dfs(g[u][i]);
        printf("%d\n", u);
    }
}

int main() {
    int i, u, w;
    scanf("%d", &n);
    for (i = 0; i < n - 1; i++) {
        scanf("%d %d", &u, &w);
        p[u]++; p[w]++;
        g[u][d[u]++] = w;
        g[w][d[w]++] = u;
    }
    dfs(1);
    return 0;
}