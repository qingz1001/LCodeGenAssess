#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3001

int n, p, r;
int spy[MAX_SIZE], bribe[MAX_SIZE];
int head[MAX_SIZE], next[MAX_SIZE], to[MAX_SIZE], tot;

void add_edge(int u, int v) {
    to[tot] = v;
    next[tot] = head[u];
    head[u] = tot++;
}

int dfs(int u, int parent) {
    if (spy[u] == 1) {
        return 1;
    }
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v == parent) continue;
        if (dfs(v, u)) {
            bribe[u] = spy[u] ? bribe[u] : bribe[v];
            return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 0; i < p; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        spy[x] = 1;
        bribe[x] = y;
    }
    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        if (!spy[i] && !dfs(i, -1)) {
            printf("NO\n%d", i);
            return 0;
        }
    }

    int min_bribe = 20001;
    for (int i = 1; i <= n; i++) {
        if (spy[i]) {
            min_bribe = bribe[i] < min_bribe ? bribe[i] : min_bribe;
        }
    }

    printf("YES\n%d", min_bribe);
    return 0;
}