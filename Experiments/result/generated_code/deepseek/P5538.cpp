#include <stdio.h>
#include <stdlib.h>

#define MOD 786433
#define MAXN 200005

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt = 0;
int a[MAXN];
int n;

void add_edge(int u, int v) {
    edges[cnt].v = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int dfs(int u, int parent, int mask) {
    int result = 0;
    mask &= a[u];
    result = (result + mask) % MOD;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].v;
        if (v != parent) {
            result = (result + dfs(v, u, mask)) % MOD;
        }
    }
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        head[i] = -1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + dfs(i, -1, (1 << 30) - 1)) % MOD;
    }

    printf("%d\n", result);
    return 0;
}