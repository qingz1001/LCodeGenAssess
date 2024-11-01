#include <stdio.h>
#include <string.h>

#define MAXN 300001

int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN], l[MAXN], r[MAXN], fa[MAXN], cnt, tot, root;
int ch[MAXN * 20][2], val[MAXN * 20], sum[MAXN * 20], tag[MAXN * 20];

void dfs1(int x) {
    l[x] = ++cnt;
    for (int i = c[x]; i; i = d[i]) {
        fa[b[i]] = x;
        dfs1(b[i]);
    }
    r[x] = ++cnt;
}

void pushup(int x) {
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]];
}

void pushdown(int x) {
    if (tag[x]) {
        if (ch[x][0]) {
            tag[ch[x][0]] += tag[x];
            sum[ch[x][0]] += tag[x] * (r[ch[x][0]] - l[ch[x][0]] + 1);
        }
        if (ch[x][1]) {
            tag[ch[x][1]] += tag[x];
            sum[ch[x][1]] += tag[x] * (r[ch[x][1]] - l[ch[x][1]] + 1);
        }
        tag[x] = 0;
    }
}

void modify(int &x, int l, int r, int ql, int qr) {
    if (!x) x = ++tot;
    if (ql <= l && r <= qr) {
        tag[x]++;
        sum[x] += r - l + 1;
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ql <= mid) modify(ch[x][0], l, mid, ql, qr);
    if (qr > mid) modify(ch[x][1], mid + 1, r, ql, qr);
    pushup(x);
}

void update(int x, int y) {
    while (x != 1) {
        modify(root, 1, n, l[fa[x]], l[x]);
        x = fa[x];
    }
    modify(root, 1, n, l[y], l[y]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a[i], &a[i + n]);
        b[i] = a[i];
        b[i + n] = a[i + n];
        c[a[i]]++;
        c[a[i + n]]++;
    }
    cnt = 0;
    dfs1(1);
    for (int i = 1; i < n; i++) {
        d[a[i]] += c[a[i + n]];
        d[a[i + n]] += c[a[i]];
        b[d[a[i]]] = a[i + n];
        b[d[a[i + n]]] = a[i];
    }
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; i++) c[a[i]]++;
    for (int i = 1; i <= n; i++) d[i] = c[i - 1] + 1;
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; i++) c[d[a[i]]++] = a[i];
    for (int i = 1; i <= n; i++) {
        update(c[i], c[i]);
        printf("%d\n", sum[root] - sum[ch[root][1]]);
    }
    return 0;
}