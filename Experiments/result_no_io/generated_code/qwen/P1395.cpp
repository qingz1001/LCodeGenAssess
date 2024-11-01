#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001

int n;
int parent[MAXN];
int size[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void union_sets(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return;
    if (size[pu] > size[pv]) {
        parent[pv] = pu;
        size[pu] += size[pv];
    } else {
        parent[pu] = pv;
        size[pv] += size[pu];
    }
}

int main() {
    scanf("%d", &n);
    init(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        union_sets(a - 1, b - 1);
    }

    int root = find(0);
    printf("%d %d\n", root + 1, size[root]);

    return 0;
}