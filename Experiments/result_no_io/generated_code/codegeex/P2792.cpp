#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define MAXK 500

typedef struct {
    int u, v;
    double w;
} Edge;

int n, m, k;
double c[MAXN + 1];
int need[MAXN + 1];
Edge edges[MAXK + 1];
double minCost[MAXN + 1][MAXN + 1];
double minPrice[MAXN + 1];

void init() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf %d", &c[i], &need[i]);
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%d %d %lf", &edges[i].u, &edges[i].v, &edges[i].w);
    }
}

void floyd() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            minCost[i][j] = c[j];
        }
    }
    for (int i = 1; i <= k; ++i) {
        minCost[edges[i].u][edges[i].v] = edges[i].w;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (minCost[i][k] + minCost[k][j] < minCost[i][j]) {
                    minCost[i][j] = minCost[i][k] + minCost[k][j];
                }
            }
        }
    }
}

double dijkstra() {
    double res = 0;
    for (int i = 1; i <= n; ++i) {
        minPrice[i] = c[i];
    }
    for (int i = 1; i <= n; ++i) {
        int u = 0;
        double min = 1e9;
        for (int j = 1; j <= n; ++j) {
            if (need[j] && minPrice[j] < min) {
                min = minPrice[j];
                u = j;
            }
        }
        if (u == 0) break;
        need[u]--;
        res += min;
        for (int v = 1; v <= n; ++v) {
            if (minPrice[v] > minPrice[u] + minCost[u][v]) {
                minPrice[v] = minPrice[u] + minCost[u][v];
            }
        }
    }
    return res;
}

int main() {
    init();
    floyd();
    double result = dijkstra();
    printf("%.2lf\n", result);
    return 0;
}