#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int a[MAXN];

void add(int l, int r, int K, int D) {
    a[l] += K;
    if (r != l) {
        a[r] += (r - l) * D;
    }
}

int query(int p) {
    return a[p];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int l, r, K, D;
            scanf("%d %d %d %d", &l, &r, &K, &D);
            add(l - 1, r - 1, K, D);
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            printf("%d\n", query(p - 1));
        }
    }

    return 0;
}