#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MAXN 110
#define MAXM 1010
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int g[MAXN][MAXN];
int tot = 0;
int head[MAXN * MAXN], nxt[MAXM * MAXN << 1], ver[MAXM * MAXN << 1], edge[MAXM * MAXN << 1];
double f[MAXN * MAXN];
int s, t;
priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > q;

void add(int x, int y, int z, double w) {
    ver[tot] = y;
    edge[tot] = z;
    f[tot] = w;
    nxt[tot] = head[x];
    head[x] = tot++;
}

void dijkstra() {
    memset(f, 0x3f, sizeof(f));
    f[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        for (int i = head[x]; ~i; i = nxt[i]) {
            int y = ver[i];
            double z = f[x] + f[i];
            if (edge[i] && f[y] > z) {
                f[y] = z;
                q.push(make_pair(z, y));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &g[i][j]);
        }
    }

    s = 0;
    t = n + m + 1;
    double ans = 0;

    for (int i = 1; i <= n; i++) {
        add(s, i, c[i], 0);
        for (int j = 1; j <= m; j++) {
            if (g[i][j]) {
                add(i, n + j, INF, 0);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        add(n + i, t, d[i], 0);
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) {
            continue;
        }
        double l = 0, r = c[i], mid;
        while (r - l > 1e-7) {
            mid = (l + r) / 2;
            double cost = a[i] * mid * mid + b[i] * mid;
            int flow = 0;
            for (int j = head[i]; ~j; j = nxt[j]) {
                if (ver[j] > n && edge[j] && f[j] == 0) {
                    flow += edge[j];
                }
            }
            if (flow > mid) {
                l = mid;
            } else {
                r = mid;
            }
        }
        add(i, t, l, a[i] * l * l + b[i] * l);
    }

    dijkstra();

    for (int i = head[t]; ~i; i = nxt[i]) {
        if (ver[i] > n && f[i] < INF) {
            ans += f[i] * f[i];
        }
    }

    printf("%.0lf\n", ans);
    printf("%.0lf/%d\n", ans, 1);

    return 0;
}