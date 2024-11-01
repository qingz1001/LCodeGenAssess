#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF LLONG_MAX

typedef long long ll;

typedef struct Edge {
    int to;
    ll cap, cost, rev;
} Edge;

typedef struct {
    int size;
    int head[100005];
    Edge edges[200005];
} Graph;

Graph G;
int n;
ll dist[100005], h[100005], prevv[100005], preve[100005];
bool inq[100005];

void add_edge(int from, int to, ll cap, ll cost) {
    G.size++;
    G.edges[G.size].to = to;
    G.edges[G.size].cap = cap;
    G.edges[G.size].cost = cost;
    G.edges[G.size].rev = G.size + 1;
    G.head[from] = G.size;
}

void add_dir_edge(int from, int to, ll cap, ll cost) {
    add_edge(from, to, cap, cost);
    add_edge(to, from, 0, -cost);
}

bool spfa(int s, int t) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        inq[i] = false;
    }
    dist[s] = 0;
    inq[s] = true;
    h[s] = 0;
    int que[100005], l = 0, r = 0;
    que[r++] = s;
    while (l < r) {
        int u = que[l++];
        inq[u] = false;
        for (int i = G.head[u]; i; i = G.edges[i].rev) {
            int v = G.edges[i].to;
            ll cap = G.edges[i].cap;
            ll cost = G.edges[i].cost;
            if (cap > 0 && dist[u] + cost + h[u] - h[v] < dist[v]) {
                dist[v] = dist[u] + cost + h[u] - h[v];
                prevv[v] = u;
                preve[v] = i;
                if (!inq[v]) {
                    inq[v] = true;
                    que[r++] = v;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        h[i] += dist[i];
    }
    return dist[t] < INF;
}

ll min_cost_max_flow(int s, int t, ll f) {
    ll flow = 0, cost = 0;
    while (f > 0 && spfa(s, t)) {
        ll d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = d < G.edges[preve[v]].cap ? d : G.edges[preve[v]].cap;
        }
        f -= d;
        flow += d;
        cost += d * h[t];
        for (int v = t; v != s; v = prevv[v]) {
            G.edges[preve[v]].cap -= d;
            G.edges[preve[v] ^ 1].cap += d;
        }
    }
    return cost;
}

int main() {
    scanf("%d", &n);
    int s = 0, t = 2 * n + 1;
    for (int i = 0; i <= t; i++) {
        G.head[i] = 0;
    }
    G.size = 1;
    for (int i = 1; i <= n; i++) {
        int d;
        scanf("%d", &d);
        add_dir_edge(s, i, d, 0);
        add_dir_edge(i + n, t, d, 0);
    }
    for (int i = 1; i <= n; i++) {
        int u;
        scanf("%d", &u);
        add_dir_edge(i, i + n, u, 0);
    }
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d", &p);
        add_dir_edge(i, i + n, INF, p);
    }
    for (int i = 1; i < n; i++) {
        int m;
        scanf("%d", &m);
        add_dir_edge(i + n, i + 1, INF, m);
    }
    for (int i = 1; i < n; i++) {
        int c;
        scanf("%d", &c);
        add_dir_edge(i, i + n, INF, c);
    }
    printf("%lld\n", min_cost_max_flow(s, t, INF));
    return 0;
}