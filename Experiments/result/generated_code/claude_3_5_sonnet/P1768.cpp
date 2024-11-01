#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N 7005
#define MAX_M 20005
#define EPS 1e-6

typedef struct Edge {
    int to, v, p;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
int n, m;
bool vis[MAX_N];
double dist[MAX_N];

void addEdge(int from, int to, int v, int p) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->v = v;
    e->p = p;
    e->next = graph[from];
    graph[from] = e;
}

bool dfs(int u, double mid) {
    vis[u] = true;
    for (Edge* e = graph[u]; e; e = e->next) {
        int v = e->to;
        double w = e->v - mid * e->p;
        if (fabs(dist[v] - (dist[u] + w)) < EPS || dist[v] < dist[u] + w) {
            dist[v] = dist[u] + w;
            if (vis[v] || dfs(v, mid)) return true;
        }
    }
    vis[u] = false;
    return false;
}

bool check(double mid) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            vis[j] = false;
            dist[j] = 0;
        }
        if (dfs(i, mid)) return true;
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int from, to, v, p;
        scanf("%d %d %d %d", &from, &to, &v, &p);
        addEdge(from, to, v, p);
    }

    double left = 0, right = 200;
    while (right - left > 1e-4) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    if (left < EPS) printf("-1\n");
    else printf("%.1f\n", left);

    return 0;
}