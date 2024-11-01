#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51
#define MAXM 501

double c[MAXN];
int need[MAXN];
double ans = 1e9;
int n, k;

typedef struct Edge {
    int v;
    double w;
    struct Edge *next;
} Edge;

typedef struct {
    Edge *first;
} Node;

Node g[MAXN];

void addEdge(int u, int v, double w) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->v = v;
    e->w = w;
    e->next = g[u].first;
    g[u].first = e;
}

void dfs(int u, double cost) {
    if (u > n) {
        if (cost < ans) ans = cost;
        return;
    }
    if (need[u] > 0) {
        need[u]--;
        dfs(u, cost + c[u]);
        need[u]++;
    }
    for (Edge *e = g[u].first; e; e = e->next) {
        need[e->v]--;
        dfs(e->v, cost + e->w);
        need[e->v]++;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %d", &c[i], &need[i]);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        int a, b;
        double p;
        scanf("%d %d %lf", &a, &b, &p);
        addEdge(a, b, p);
    }
    dfs(1, 0);
    printf("%.2lf\n", ans);
    return 0;
}