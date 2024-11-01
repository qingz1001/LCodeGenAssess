#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50005
#define MAX_M 100005
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

struct Edge {
    int to, next;
    ll cost;
} edge[MAX_N * 2];

int head[MAX_N], ecnt;
int n, m;
ll dis[MAX_N];
int fa[MAX_N], dep[MAX_N], son[MAX_N], top[MAX_N], sz[MAX_N];

void addEdge(int u, int v, ll w) {
    edge[ecnt] = (struct Edge){v, head[u], w};
    head[u] = ecnt++;
}

void dfs1(int u, int f) {
    fa[u] = f;
    sz[u] = 1;
    dep[u] = dep[f] + 1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == f) continue;
        dis[v] = dis[u] + edge[i].cost;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

ll getDis(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

struct Plan {
    int u, v;
    ll cost;
} plan[MAX_M];

ll tree[MAX_N * 4], lazy[MAX_N * 4];

void pushup(int rt) {
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void pushdown(int rt, int l, int r) {
    if (lazy[rt]) {
        int mid = (l + r) >> 1;
        tree[rt << 1] += lazy[rt] * (mid - l + 1);
        tree[rt << 1 | 1] += lazy[rt] * (r - mid);
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void update(int rt, int l, int r, int L, int R, ll val) {
    if (L <= l && r <= R) {
        tree[rt] += val * (r - l + 1);
        lazy[rt] += val;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt << 1, l, mid, L, R, val);
    if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R, val);
    pushup(rt);
}

ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res += query(rt << 1, l, mid, L, R);
    if (R > mid) res += query(rt << 1 | 1, mid + 1, r, L, R);
    return res;
}

void updatePath(int u, int v, ll val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        update(1, 1, n, dep[top[u]], dep[u], val);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    update(1, 1, n, dep[u], dep[v], val);
}

ll queryPath(int u, int v) {
    ll res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int t = u; u = v; v = t;
        }
        res += query(1, 1, n, dep[top[u]], dep[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int t = u; u = v; v = t;
    }
    res += query(1, 1, n, dep[u], dep[v]);
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(head, -1, sizeof(head));
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
        memset(son, 0, sizeof(son));
        ecnt = 0;

        scanf("%d", &n);
        for (int i = 1; i < n; i++) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }

        dfs1(1, 0);
        dfs2(1, 1);

        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%lld", &plan[i].u, &plan[i].v, &plan[i].cost);
        }

        ll ans = -INF;
        for (int i = 1; i <= m; i++) {
            updatePath(plan[i].u, plan[i].v, 1);
            for (int j = i + 1; j <= m; j++) {
                ll common = queryPath(plan[j].u, plan[j].v);
                if (common > 0) {
                    ll gain = getDis(plan[i].u, plan[i].v) + getDis(plan[j].u, plan[j].v) - common;
                    ll cost = plan[i].cost + plan[j].cost;
                    ans = ans > gain - cost ? ans : gain - cost;
                }
            }
            updatePath(plan[i].u, plan[i].v, -1);
        }

        if (ans == -INF) {
            printf("F\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}