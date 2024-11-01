#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 100005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Edge {
    int to, next;
    ll cost;
} edge[MAXN << 1];

struct Plan {
    int x, y;
    ll v;
} plan[MAXM];

int head[MAXN], tot;
int fa[MAXN], dep[MAXN], size[MAXN], son[MAXN], top[MAXN];
int dfn[MAXN], rnk[MAXN], cnt;
ll dis[MAXN];

void init(int n) {
    memset(head, -1, sizeof(int) * (n + 1));
    tot = 0;
    cnt = 0;
}

void addEdge(int u, int v, ll w) {
    edge[tot] = (struct Edge){v, head[u], w};
    head[u] = tot++;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    son[u] = -1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == f) continue;
        dis[v] = dis[u] + edge[i].cost;
        dfs1(v, u);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            v = fa[top[v]];
        else
            u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

ll getPathCost(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

struct SegTree {
    ll max[MAXN << 2], lazy[MAXN << 2];

    void pushup(int rt) {
        max[rt] = max[rt << 1] > max[rt << 1 | 1] ? max[rt << 1] : max[rt << 1 | 1];
    }

    void pushdown(int rt) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            max[rt << 1] += lazy[rt];
            max[rt << 1 | 1] += lazy[rt];
            lazy[rt] = 0;
        }
    }

    void build(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            max[rt] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        pushup(rt);
    }

    void update(int L, int R, ll v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            lazy[rt] += v;
            max[rt] += v;
            return;
        }
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (L <= mid) update(L, R, v, l, mid, rt << 1);
        if (R > mid) update(L, R, v, mid + 1, r, rt << 1 | 1);
        pushup(rt);
    }

    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return max[rt];
        pushdown(rt);
        int mid = (l + r) >> 1;
        ll res = -INF;
        if (L <= mid) res = query(L, R, l, mid, rt << 1);
        if (R > mid) res = res > query(L, R, mid + 1, r, rt << 1 | 1) ? res : query(L, R, mid + 1, r, rt << 1 | 1);
        return res;
    }
} seg;

void updatePath(int u, int v, ll val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            v = fa[top[v]];
        else {
            seg.update(dfn[top[u]], dfn[u], val, 1, cnt, 1);
            u = fa[top[u]];
        }
    }
    if (dep[u] > dep[v]) {
        int tmp = u;
        u = v;
        v = tmp;
    }
    seg.update(dfn[u], dfn[v], val, 1, cnt, 1);
}

ll solve(int n, int m) {
    seg.build(1, cnt, 1);
    ll ans = -INF;
    for (int i = 1; i <= m; i++) {
        int x = plan[i].x, y = plan[i].y;
        ll v = plan[i].v;
        updatePath(x, y, 1);
        ll tmp = seg.query(1, cnt, 1, cnt, 1);
        updatePath(x, y, -1);
        if (tmp > 1) {
            ll cur = getPathCost(x, y) - v + seg.max[1] - v;
            ans = ans > cur ? ans : cur;
        }
    }
    return ans == -INF ? -1 : ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        init(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        dfs1(1, 0);
        dfs2(1, 1);
        int m;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%lld", &plan[i].x, &plan[i].y, &plan[i].v);
        }
        ll ans = solve(n, m);
        if (ans == -1)
            printf("F\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}