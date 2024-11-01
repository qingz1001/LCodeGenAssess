#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50001
#define MAX_M 100001
#define MAX_BIT 64

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    struct Edge* next;
};

struct Edge* graph[MAX_N];
int n, m;
ll dp[MAX_N][MAX_BIT];

void add_edge(int from, int to, ll weight) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = to;
    e->weight = weight;
    e->next = graph[from];
    graph[from] = e;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void dfs(int u, int p) {
    struct Edge* e;
    for (e = graph[u]; e; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        for (int i = 0; i < MAX_BIT; i++) {
            ll val = dp[u][i] ^ e->weight;
            dp[v][i] = max(dp[v][i], val);
        }
        dfs(v, u);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    memset(dp, 0, sizeof(dp));
    dfs(1, 0);

    ll ans = 0;
    for (int i = 0; i < MAX_BIT; i++) {
        ans = max(ans, dp[n][i]);
    }

    printf("%lld\n", ans);
    return 0;
}