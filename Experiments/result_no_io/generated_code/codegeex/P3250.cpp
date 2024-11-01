#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100005, M = 200005;
int n, m, tot, head[N], to[M], nxt[M], fa[N], dep[N], top[N], son[N], siz[N], dfn[N], idx, val[N], tag[N], ans[N], que[N], hd, tl;

void add(int x, int y) {
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

void dfs1(int x, int f) {
    fa[x] = f;
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == f) continue;
        dfs1(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int t) {
    top[x] = t;
    dfn[x] = ++idx;
    val[idx] = x;
    if (son[x]) dfs2(son[x], t);
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}

void pushdown(int l, int r) {
    if (tag[l] == 0) return;
    int mid = (l + r) >> 1;
    swap(que[mid], que[r]);
    swap(tag[mid], tag[r]);
    if (l < mid) pushdown(l, mid - 1);
    if (mid < r) pushdown(mid + 1, r);
    tag[l] = tag[r] = 0;
}

void update(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        pushdown(dfn[top[x]], dfn[x]);
        swap(que[dfn[top[x]]], que[dfn[x]]);
        swap(tag[dfn[top[x]]], tag[dfn[x]]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    pushdown(dfn[x], dfn[y]);
    swap(que[dfn[x]], que[dfn[y]]);
    swap(tag[dfn[x]], tag[dfn[y]]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        int op, x, y, v;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d", &x, &y, &v);
            update(x, y);
            que[dfn[x]] = que[dfn[y]] = v;
            tag[dfn[x]] = tag[dfn[y]] = 1;
        } else if (op == 1) {
            scanf("%d", &x);
            pushdown(dfn[x], dfn[x] + siz[x] - 1);
            que[dfn[x]] = 0;
            tag[dfn[x]] = 1;
        } else {
            scanf("%d", &x);
            pushdown(dfn[x], dfn[x] + siz[x] - 1);
            int mx = -1;
            for (int i = dfn[x]; i <= dfn[x] + siz[x] - 1; i++) {
                if (que[i] > mx && tag[i] == 0) mx = que[i];
            }
            ans[i] = mx;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (ans[i] != -1) printf("%d\n", ans[i]);
    }
    return 0;
}