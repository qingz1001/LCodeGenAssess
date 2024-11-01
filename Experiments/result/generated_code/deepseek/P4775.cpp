#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 100005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to, next;
    ll cost;
} edges[MAXN * 2];

int head[MAXN], cnt;

void add_edge(int u, int v, ll w) {
    edges[cnt].to = v;
    edges[cnt].cost = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

struct Plan {
    int x, y;
    ll cost;
} plans[MAXM];

int n, m;
ll max_diff = -INF;

void dfs(int u, int parent, ll cost, ll* max_cost, ll* min_cost) {
    *max_cost = *min_cost = cost;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        ll max_c, min_c;
        dfs(v, u, cost + edges[i].cost, &max_c, &min_c);
        if (max_c > *max_cost) *max_cost = max_c;
        if (min_c < *min_cost) *min_cost = min_c;
    }
}

void solve() {
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            ll max_cost_i, min_cost_i, max_cost_j, min_cost_j;
            dfs(plans[i].x, -1, 0, &max_cost_i, &min_cost_i);
            dfs(plans[j].x, -1, 0, &max_cost_j, &min_cost_j);
            if (max_cost_i == max_cost_j && min_cost_i == min_cost_j) {
                ll diff = (max_cost_i - min_cost_i) - (plans[i].cost + plans[j].cost);
                if (diff > max_diff) max_diff = diff;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            ll c;
            scanf("%d %d %lld", &a, &b, &c);
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %lld", &plans[i].x, &plans[i].y, &plans[i].cost);
        }
        max_diff = -INF;
        solve();
        if (max_diff == -INF) {
            printf("F\n");
        } else {
            printf("%lld\n", max_diff);
        }
    }
    return 0;
}