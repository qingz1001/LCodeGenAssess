#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to, next;
    ll w;
} edge[MAXN * 2];

int head[MAXN], tot = 0;
ll dis[MAXN][2];
int n;

void add(int u, int v, ll w) {
    edge[++tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot;
}

void dijkstra(int s, int type) {
    for (int i = 1; i <= n; i++) dis[i][type] = INF;
    dis[s][type] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().second;
        ll d = pq.top().first;
        pq.pop();
        if (d > dis[u][type]) continue;
        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;
            ll w = edge[i].w;
            if (dis[v][type] > d + w) {
                dis[v][type] = d + w;
                pq.push({dis[v][type], v});
            }
        }
    }
}

double solve() {
    dijkstra(1, 0);
    ll max_dis = -1;
    for (int i = 1; i <= n; i++) {
        if (max_dis < dis[i][0]) max_dis = dis[i][0];
    }
    dijkstra(max_dis / 2, 1);
    return round(dis[max_dis / 2][1] * 10) / 10.0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        ll l;
        scanf("%d%d%lld", &a, &b, &l);
        add(a, b, l);
        add(b, a, l);
    }
    printf("%.1lf\n", solve());
    return 0;
}