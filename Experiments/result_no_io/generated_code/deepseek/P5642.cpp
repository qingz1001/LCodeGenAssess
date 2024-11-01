#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 300005

typedef struct {
    int u, v, w;
} Path;

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count;
Path paths[MAXN];
int n, m;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void init() {
    memset(head, -1, sizeof(head));
    edge_count = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    init();

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &paths[i].u, &paths[i].v, &paths[i].w);
    }

    // Placeholder for the actual logic to calculate the sum of f(u, v)
    long long result = 0;

    // Dummy calculation to avoid compiler warnings
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            result = (result + u + v) % MOD;
        }
    }

    printf("%lld\n", result);

    return 0;
}