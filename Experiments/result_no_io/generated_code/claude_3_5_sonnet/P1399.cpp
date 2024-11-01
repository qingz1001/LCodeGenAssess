#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to, next;
    ll len;
} edge[MAXN * 2];

int head[MAXN], cnt;
int n;
ll dis[MAXN], max_dis[MAXN];

void add_edge(int u, int v, ll w) {
    edge[cnt].to = v;
    edge[cnt].len = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int fa) {
    max_dis[u] = 0;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dis[v] = dis[u] + edge[i].len;
        dfs(v, u);
        max_dis[u] = fmax(max_dis[u], max_dis[v] + edge[i].len);
    }
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1, 0);
    int s = 1;
    for (int i = 2; i <= n; i++)
        if (dis[i] > dis[s]) s = i;

    memset(dis, 0, sizeof(dis));
    dfs(s, 0);

    double ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = fmin(ans, fmax(dis[i], max_dis[i]));
        if (i > 1) {
            int fa = 0;
            for (int j = head[i]; ~j; j = edge[j].next)
                if (dis[edge[j].to] < dis[i]) {
                    fa = edge[j].to;
                    break;
                }
            double left = fmax(dis[fa], max_dis[i]);
            double right = fmax(dis[i], max_dis[fa]);
            double x = (right - left + edge[head[i]].len) / 2.0;
            if (x >= 0 && x <= edge[head[i]].len)
                ans = fmin(ans, fmax(left + x, right - x));
        }
    }

    printf("%.1f\n", ans);
    return 0;
}