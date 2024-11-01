#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

int n, a[MAXN], head[MAXN], tot, fa[MAXN], sum[MAXN << 2], tag[MAXN << 2];

struct Edge {
    int to, next;
} edge[MAXN << 1];

void add(int u, int v) {
    edge[++tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}

void push_up(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void push_down(int rt, int m) {
    if (tag[rt]) {
        tag[rt << 1] += tag[rt];
        tag[rt << 1 | 1] += tag[rt];
        sum[rt << 1] += tag[rt] * (m - (m >> 1));
        sum[rt << 1 | 1] += tag[rt] * (m >> 1);
        tag[rt] = 0;
    }
}

void build(int l, int r, int rt) {
    if (l == r) {
        sum[rt] = 1;
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    push_up(rt);
}

void update(int L, int R, int c, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tag[rt] += c;
        sum[rt] += c * (r - l + 1);
        return;
    }
    push_down(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, c, l, m, rt << 1);
    if (R > m) update(L, R, c, m + 1, r, rt << 1 | 1);
    push_up(rt);
}

int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    push_down(rt, r - l + 1);
    int m = (l + r) >> 1, ret = 0;
    if (L <= m) ret += query(L, R, l, m, rt << 1);
    if (R > m) ret += query(L, R, m + 1, r, rt << 1 | 1);
    return ret;
}

void dfs(int x, int f) {
    fa[x] = f;
    for (int i = head[x]; i; i = edge[i].next) {
        int y = edge[i].to;
        if (y != f) {
            dfs(y, x);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    build(1, n, 1);
    for (int i = 1; i < n; i++) {
        update(a[i], n, -1, 1, n, 1);
        if (fa[a[i]] != 0) {
            update(fa[a[i]], n, 1, 1, n, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", query(a[i], a[i], 1, n, 1));
    }
    return 0;
}