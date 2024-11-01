#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int n, m;
int *v, *parent, *size, *xor_value;

void init() {
    v = (int *)malloc((n + 1) * sizeof(int));
    parent = (int *)malloc((n + 1) * sizeof(int));
    size = (int *)malloc((n + 1) * sizeof(int));
    xor_value = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        v[i] = 0;
        parent[i] = i;
        size[i] = 1;
        xor_value[i] = 0;
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
        xor_value[pu] ^= xor_value[pv];
    } else {
        parent[pu] = pv;
        size[pv] += size[pu];
        xor_value[pv] ^= xor_value[pu];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    init();

    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        xor_value[i] = v[i];
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        union_sets(a, b);
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'Q') {
            int k;
            scanf("%d", &k);
            int result = 0;
            for (int i = 1; i <= n; i++) {
                if (find(i) == i && (xor_value[i] ^ k) == 0) {
                    result++;
                }
            }
            printf("%d\n", result % MOD);
        } else if (op[0] == 'C') {
            int x, y;
            scanf("%d %d", &x, &y);
            v[x] = y;
            xor_value[x] = y;
            for (int i = x; i != parent[i]; i = parent[i]) {
                xor_value[parent[i]] ^= xor_value[i];
            }
        }
    }

    free(v);
    free(parent);
    free(size);
    free(xor_value);

    return 0;
}