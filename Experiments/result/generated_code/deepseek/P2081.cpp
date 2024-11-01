#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    Edge edges[MAXN * 2];
    int head[MAXN], cnt;
} Graph;

Graph G;
int n, m;
double dp[MAXN], dp2[MAXN];
int degree[MAXN];

void add_edge(int u, int v, int w) {
    G.edges[G.cnt].to = v;
    G.edges[G.cnt].weight = w;
    G.edges[G.cnt].next = G.head[u];
    G.head[u] = G.cnt++;
}

void dfs1(int u, int fa) {
    dp[u] = 0;
    int count = 0;
    for (int i = G.head[u]; i != -1; i = G.edges[i].next) {
        int v = G.edges[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        dp[u] += dp[v] + G.edges[i].weight;
        count++;
    }
    if (count) dp[u] /= count;
}

void dfs2(int u, int fa) {
    int count = 0;
    double sum = 0;
    for (int i = G.head[u]; i != -1; i = G.edges[i].next) {
        int v = G.edges[i].to;
        if (v == fa) continue;
        count++;
        sum += dp[v] + G.edges[i].weight;
    }
    for (int i = G.head[u]; i != -1; i = G.edges[i].next) {
        int v = G.edges[i].to;
        if (v == fa) continue;
        dp2[v] = (sum - (dp[v] + G.edges[i].weight)) / (count - 1) + G.edges[i].weight;
        dfs2(v, u);
    }
}

int main() {
    memset(G.head, -1, sizeof(G.head));
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        degree[u]++;
        degree[v]++;
    }

    if (m == n - 1) {
        dfs1(1, -1);
        printf("%.5f\n", dp[1]);
    } else {
        dfs1(1, -1);
        dfs2(1, -1);
        double ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += (dp[i] + dp2[i]) / 2;
        }
        printf("%.5f\n", ans / n);
    }

    return 0;
}