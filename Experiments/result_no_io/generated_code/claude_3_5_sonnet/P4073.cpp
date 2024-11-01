#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005
#define MAX_Q 100005
#define INF 1e18

typedef long long ll;
typedef double db;

struct Point {
    db x, y;
} p[MAX_N];

struct Edge {
    int u, v, h;
} e[MAX_M];

struct Query {
    db ax, ay, bx, by;
} q[MAX_Q];

int n, m, Q;
int fa[MAX_N], sz[MAX_N], dep[MAX_N];
int lca[MAX_N][20], mxe[MAX_N][20];

int cmp(const void *a, const void *b) {
    return ((struct Edge*)a)->h - ((struct Edge*)b)->h;
}

int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) {
        fa[x] = y;
        sz[y] += sz[x];
    } else {
        fa[y] = x;
        sz[x] += sz[y];
    }
}

db cross(db x1, db y1, db x2, db y2) {
    return x1 * y2 - x2 * y1;
}

int sgn(db x) {
    return fabs(x) < 1e-8 ? 0 : (x > 0 ? 1 : -1);
}

int check(db x1, db y1, db x2, db y2, db x3, db y3, db x4, db y4) {
    return sgn(cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1)) * 
           sgn(cross(x2 - x1, y2 - y1, x4 - x1, y4 - y1)) <= 0 &&
           sgn(cross(x4 - x3, y4 - y3, x1 - x3, y1 - y3)) * 
           sgn(cross(x4 - x3, y4 - y3, x2 - x3, y2 - y3)) <= 0;
}

void dfs(int u, int f, int d) {
    dep[u] = d;
    lca[u][0] = f;
    for (int i = 1; i < 20; i++) {
        lca[u][i] = lca[lca[u][i-1]][i-1];
        mxe[u][i] = fmax(mxe[u][i-1], mxe[lca[u][i-1]][i-1]);
    }
}

int getLCA(int u, int v) {
    if (dep[u] < dep[v]) {
        int tmp = u; u = v; v = tmp;
    }
    int diff = dep[u] - dep[v];
    int mx = 0;
    for (int i = 0; i < 20; i++) {
        if ((diff >> i) & 1) {
            mx = fmax(mx, mxe[u][i]);
            u = lca[u][i];
        }
    }
    if (u == v) return mx;
    for (int i = 19; i >= 0; i--) {
        if (lca[u][i] != lca[v][i]) {
            mx = fmax(mx, fmax(mxe[u][i], mxe[v][i]));
            u = lca[u][i];
            v = lca[v][i];
        }
    }
    return fmax(mx, fmax(mxe[u][0], mxe[v][0]));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        fa[i] = i;
        sz[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].h);
    }
    qsort(e + 1, m, sizeof(struct Edge), cmp);
    
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        if (find(u) != find(v)) {
            unite(u, v);
            mxe[u][0] = mxe[v][0] = e[i].h;
            dfs(u, v, dep[v] + 1);
            dfs(v, u, dep[u] + 1);
        }
    }
    
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        scanf("%lf%lf%lf%lf", &q[i].ax, &q[i].ay, &q[i].bx, &q[i].by);
        int cnt = 0, flag = 0;
        for (int j = 1; j <= m; j++) {
            if (check(q[i].ax, q[i].ay, q[i].bx, q[i].by, p[e[j].u].x, p[e[j].u].y, p[e[j].v].x, p[e[j].v].y)) {
                cnt++;
                if (cnt == 1) flag = j;
            }
        }
        if (cnt == 0) printf("0\n");
        else if (cnt == 1) printf("%d\n", e[flag].h);
        else printf("%d\n", getLCA(e[flag].u, e[flag].v));
    }
    return 0;
}