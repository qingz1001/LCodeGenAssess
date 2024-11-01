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

int head[MAXN], edge_cnt = 0;

void add_edge(int u, int v, ll c) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].cost = c;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

struct Plan {
    int x, y;
    ll v;
} plans[MAXM];

int n, m;
ll dist[MAXN];
int parent[MAXN];

void dfs(int u, int p) {
    parent[u] = p;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        dist[v] = dist[u] + edges[i].cost;
        dfs(v, u);
    }
}

ll max_profit = -INF;

void check_plans(int i, int j) {
    int x1 = plans[i].x, y1 = plans[i].y;
    int x2 = plans[j].x, y2 = plans[j].y;
    ll v1 = plans[i].v, v2 = plans[j].v;

    ll total_cost = v1 + v2;
    ll total_profit = 0;

    int common_edges = 0;
    int path1[MAXN], path2[MAXN];
    int len1 = 0, len2 = 0;

    while (x1 != y1) {
        path1[len1++] = x1;
        x1 = parent[x1];
    }
    path1[len1++] = y1;

    while (x2 != y2) {
        path2[len2++] = x2;
        x2 = parent[x2];
    }
    path2[len2++] = y2;

    for (int k = 0; k < len1; k++) {
        for (int l = 0; l < len2; l++) {
            if (path1[k] == path2[l]) {
                common_edges++;
                break;
            }
        }
    }

    if (common_edges > 0) {
        total_profit = 0; // Calculate the total profit based on the common edges
        if (total_profit - total_cost > max_profit) {
            max_profit = total_profit - total_cost;
        }
    }
}

int main() {
    freopen("center.in", "r", stdin);
    freopen("center.out", "w", stdout);

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        memset(head, -1, sizeof(head));
        edge_cnt = 0;

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            ll c;
            scanf("%d %d %lld", &a, &b, &c);
            add_edge(a, b, c);
            add_edge(b, a, c);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %lld", &plans[i].x, &plans[i].y, &plans[i].v);
        }

        dist[1] = 0;
        dfs(1, -1);

        max_profit = -INF;
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                check_plans(i, j);
            }
        }

        if (max_profit == -INF) {
            printf("F\n");
        } else {
            printf("%lld\n", max_profit);
        }
    }

    return 0;
}