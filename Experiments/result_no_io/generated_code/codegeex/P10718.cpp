#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

int main() {
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);

    int x[n], y[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    int u[m], v[m];
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u[i], &v[i]);
    }

    int l[k], c[100005];
    for (int i = 0; i < k; i++) {
        scanf("%d", &l[i]);
        for (int j = 0; j < l[i]; j++) {
            scanf("%d", &c[i * l[i] + j]);
        }
    }

    int z[q];
    for (int i = 0; i < q; i++) {
        scanf("%d", &z[i]);
    }

    // 在这里编写你的算法逻辑

    return 0;
}