#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 20
#define MAXE 200

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXE * 2];
int head[MAXM + 1], edge_count = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;

    edges[edge_count].to = u;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[v];
    head[v] = edge_count++;
}

int n, m, k, e;
int dis[MAXM + 1];
int blocked[MAXM + 1][MAXN + 1];
int dp[MAXN + 1];

void dijkstra(int start, int day) {
    for (int i = 1; i <= m; i++) dis[i] = INT_MAX;
    dis[start] = 0;
    int visited[MAXM + 1] = {0};

    for (int i = 1; i <= m; i++) {
        int min_dis = INT_MAX, u = -1;
        for (int j = 1; j <= m; j++) {
            if (!visited[j] && dis[j] < min_dis) {
                min_dis = dis[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to, w = edges[j].weight;
            if (!blocked[v][day] && dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &e);
    for (int i = 1; i <= m; i++) head[i] = -1;

    for (int i = 0; i < e; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; i++) {
        int p, a, b;
        scanf("%d %d %d", &p, &a, &b);
        for (int j = a; j <= b; j++) blocked[p][j] = 1;
    }

    for (int i = 1; i <= n; i++) {
        dijkstra(1, i);
        dp[i] = dis[m];
        for (int j = 1; j < i; j++) {
            dijkstra(1, j);
            if (dis[m] != INT_MAX) {
                dp[i] = dp[i] < dp[j] + k + dis[m] * (i - j) ? dp[i] : dp[j] + k + dis[m] * (i - j);
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}