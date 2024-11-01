#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50005
#define MAX_M 100005

int n;
int head[MAX_N], to[MAX_M], nxt[MAX_M], cnt;
int size[MAX_N], dp[MAX_N];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dp[v] = dp[u] - size[v] + (n - size[v]);
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs1(1, 0);
    for (int i = 1; i <= n; i++) {
        dp[1] += size[i] - 1;
    }
    dfs2(1, 0);

    int min_node = 1, min_dist = dp[1];
    for (int i = 2; i <= n; i++) {
        if (dp[i] < min_dist) {
            min_node = i;
            min_dist = dp[i];
        }
    }

    printf("%d %d\n", min_node, min_dist);
    return 0;
}