#include <stdio.h>
#include <stdlib.h>

#define MAXN 301
#define INF 1000000000

int n;
int W[MAXN], P[MAXN][MAXN];
int min_cost[MAXN], in_mst[MAXN];

void init() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &W[i]);
        min_cost[i] = W[i];
        in_mst[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &P[i][j]);
        }
    }
}

int find_min() {
    int min_index = 0, min_value = INF;
    for (int i = 1; i <= n; i++) {
        if (!in_mst[i] && min_cost[i] < min_value) {
            min_index = i;
            min_value = min_cost[i];
        }
    }
    return min_index;
}

void prim() {
    for (int i = 1; i <= n; i++) {
        int u = find_min();
        in_mst[u] = 1;
        for (int v = 1; v <= n; v++) {
            if (!in_mst[v] && P[u][v] < min_cost[v]) {
                min_cost[v] = P[u][v];
            }
        }
    }
}

int main() {
    init();
    prim();
    int total_cost = 0;
    for (int i = 1; i <= n; i++) {
        total_cost += min_cost[i];
    }
    printf("%d\n", total_cost);
    return 0;
}