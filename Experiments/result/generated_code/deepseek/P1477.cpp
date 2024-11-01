#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXM 1000005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], deg[MAXN], vis[MAXN], d[MAXN], cnt = 0;
int n, m;

void add_edge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void dfs(int u, int depth) {
    vis[u] = 1;
    d[u] = depth;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) {
            dfs(v, depth + 1);
        } else {
            int cycle_length = abs(d[u] - d[v] + 1);
            if (cycle_length > 0) {
                deg[u] = gcd(deg[u], cycle_length);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        deg[i] = 0;
        vis[i] = 0;
        d[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 0);
        }
    }

    int max_k = 0, min_k = 3;
    bool valid = true;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 0) {
            max_k = gcd(max_k, deg[i]);
        }
    }

    if (max_k == 0) {
        max_k = n;
    }

    if (max_k < 3) {
        valid = false;
    }

    if (valid) {
        printf("%d %d\n", max_k, 3);
    } else {
        printf("-1 -1\n");
    }

    return 0;
}