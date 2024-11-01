#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edge_count = 0;
int p[MAXN];
int n;
double k;

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int visited[MAXN], in_cycle[MAXN], cycle_start, cycle_end;

int find_cycle(int u, int parent) {
    visited[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent) continue;
        if (visited[v]) {
            cycle_start = v;
            cycle_end = u;
            return 1;
        }
        if (find_cycle(v, u)) {
            if (cycle_start != -1) {
                in_cycle[u] = 1;
            }
            if (u == cycle_start) {
                cycle_start = -1;
            }
            return 1;
        }
    }
    return 0;
}

double dp[MAXN][2];

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = p[u] * k;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == parent || in_cycle[v]) continue;
        dfs(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += dp[v][0];
    }
    if (dp[u][0] < dp[u][1]) {
        dp[u][0] = dp[u][1];
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%lf", &k);

    find_cycle(0, -1);

    double total_profit = 0;
    for (int i = 0; i < n; i++) {
        if (in_cycle[i]) {
            dfs(i, -1);
            total_profit += dp[i][0];
        }
    }

    printf("%.1f\n", total_profit);
    return 0;
}