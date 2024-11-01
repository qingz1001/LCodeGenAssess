#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000001

int n, m;
int a[MAXN];
int last[MAXN];
int ans[MAXN];
int tree[MAXN];

inline int lowbit(int x) {
    return x & (-x);
}

void update(int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

struct Query {
    int l, r, id;
} q[MAXN];

int cmp(const void *a, const void *b) {
    return ((Query*)a)->r - ((Query*)b)->r;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }

    m = read();
    for (int i = 0; i < m; i++) {
        q[i].l = read();
        q[i].r = read();
        q[i].id = i;
    }

    qsort(q, m, sizeof(Query), cmp);

    memset(last, 0, sizeof(last));
    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (last[a[i]]) update(last[a[i]], -1);
        update(i, 1);
        last[a[i]] = i;

        while (j < m && q[j].r == i) {
            ans[q[j].id] = query(q[j].r) - query(q[j].l - 1);
            j++;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}