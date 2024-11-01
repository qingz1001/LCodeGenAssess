#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 100005
#define MAX_Q 100005
#define INF 1e18

typedef long long ll;

struct Point {
    ll x, y;
} points[MAX_N];

struct Edge {
    int u, v, h;
} edges[MAX_M];

struct Query {
    double ax, ay, bx, by;
} queries[MAX_Q];

int n, m, q;
int fa[MAX_N], size[MAX_N], mx[MAX_N];

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void unite(int x, int y, int h) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) {
        int t = x; x = y; y = t;
    }
    fa[y] = x;
    size[x] += size[y];
    mx[x] = mx[y] = (mx[x] > mx[y] ? mx[x] : mx[y]);
    mx[x] = (mx[x] > h ? mx[x] : h);
}

int ccw(Point a, Point b, Point c) {
    ll area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0) return 1;
    if (area < 0) return -1;
    return 0;
}

int intersect(Point a, Point b, Point c, Point d) {
    return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &points[i].x, &points[i].y);
        fa[i] = i;
        size[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%lf%lf%lf%lf", &queries[i].ax, &queries[i].ay, &queries[i].bx, &queries[i].by);
    }

    for (int i = 1; i <= m; i++) {
        unite(edges[i].u, edges[i].v, edges[i].h);
    }

    for (int i = 1; i <= q; i++) {
        Point a = {(ll)(queries[i].ax * 2), (ll)(queries[i].ay * 2)};
        Point b = {(ll)(queries[i].bx * 2), (ll)(queries[i].by * 2)};
        int ans = 0, flag = 0;

        for (int j = 1; j <= m; j++) {
            Point c = points[edges[j].u];
            Point d = points[edges[j].v];
            if (intersect(a, b, c, d)) {
                int fu = find(edges[j].u);
                int fv = find(edges[j].v);
                if (fu != fv) {
                    flag = 1;
                    break;
                }
                if (edges[j].h > ans) ans = edges[j].h;
            }
        }

        if (flag) printf("-1\n");
        else printf("%d\n", ans);
    }

    return 0;
}