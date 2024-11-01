#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, m;
int head[MAXN], to[MAXN * 2], next[MAXN * 2], edge_cnt = 0;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

int dfs(int u, int fa) {
    int cnt = 1;
    for (int i = head[u]; ~i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        cnt += dfs(v, u);
    }
    return cnt;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    int result[n + 1];
    for (int i = 1; i <= n; i++) {
        result[i] = dfs(i, -1);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}