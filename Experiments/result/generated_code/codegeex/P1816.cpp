#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int a[MAXN], st[MAXN][20];

void build(int k, int l, int r) {
    if (l == r) {
        st[k][0] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(k * 2, l, m);
    build(k * 2 + 1, m + 1, r);
    st[k][0] = st[k * 2][0] < st[k * 2 + 1][0] ? st[k * 2][0] : st[k * 2 + 1][0];
}

int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return st[k][0];
    }
    int m = (l + r) / 2;
    int min1 = MAXN, min2 = MAXN;
    if (x <= m) min1 = query(k * 2, l, m, x, y);
    if (y > m) min2 = query(k * 2 + 1, m + 1, r, x, y);
    return min1 < min2 ? min1 : min2;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    build(1, 1, m);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d ", query(1, 1, m, x, y));
    }
    printf("\n");
    return 0;
}