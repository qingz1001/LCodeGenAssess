#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, q;
int parent[MAXN];
int size[MAXN];

void init() {
    for (int i = 0; i <= n; i++) {
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

void merge(int u, int v) {
    int pu = find(u), pv = find(v);
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
    init();
    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        merge(i, p);
    }
    scanf("%d", &q);
    while (q--) {
        char op[10];
        int x;
        scanf("%s %d", op, &x);
        if (op[0] == 'i') {
            int root = find(x);
            printf("%d\n", size[root]);
            for (int i = 1; i <= n; i++) {
                if (find(i) == root && i != x) {
                    merge(i, x);
                }
            }
        } else {
            int root = find(x);
            printf("%d\n", size[root]);
            for (int i = 1; i <= n; i++) {
                if (find(i) == root) {
                    merge(i, 0);
                }
            }
        }
    }
    return 0;
}