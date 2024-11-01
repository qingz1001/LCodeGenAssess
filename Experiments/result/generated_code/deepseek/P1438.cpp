#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int a[MAXN];
int n, m;

void add_arithmetic_sequence(int l, int r, int K, int D) {
    for (int i = l; i <= r; i++) {
        a[i] += K + (i - l) * D;
    }
}

int query(int p) {
    return a[p];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int l, r, K, D;
            scanf("%d %d %d %d", &l, &r, &K, &D);
            add_arithmetic_sequence(l, r, K, D);
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            printf("%d\n", query(p));
        }
    }

    return 0;
}