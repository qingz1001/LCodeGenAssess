#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50005

typedef struct {
    int to, weight;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int army[MAXN], n, m;
int dist[MAXN], parent[MAXN];

void add_edge(int u, int v, int w) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

void dfs(int node, int par, int d) {
    parent[node] = par;
    dist[node] = d;
    for (Edge *e = graph[node]; e != NULL; e = e->next) {
        if (e->to != par) {
            dfs(e->to, node, d + e->weight);
        }
    }
}

int check(int limit) {
    int covered[MAXN] = {0};
    int moved[MAXN] = {0};
    for (int i = 0; i < m; i++) {
        int pos = army[i];
        int time = 0;
        while (pos != 1 && time + dist[pos] <= limit) {
            time += dist[pos];
            pos = parent[pos];
        }
        if (pos != 1) {
            covered[pos] = 1;
        } else {
            moved[pos] = 1;
        }
    }
    int need_cover = 0;
    for (Edge *e = graph[1]; e != NULL; e = e->next) {
        if (!covered[e->to]) {
            need_cover = 1;
            break;
        }
    }
    if (!need_cover) return 1;
    for (int i = 0; i < m; i++) {
        int pos = army[i];
        int time = 0;
        while (pos != 1 && time + dist[pos] <= limit) {
            time += dist[pos];
            pos = parent[pos];
        }
        if (pos == 1 && moved[pos]) {
            covered[pos] = 1;
        }
    }
    for (Edge *e = graph[1]; e != NULL; e = e->next) {
        if (!covered[e->to]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &army[i]);
    }

    dfs(1, -1, 0);

    int left = 0, right = INT_MAX, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}