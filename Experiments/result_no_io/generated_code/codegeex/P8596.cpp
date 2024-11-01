#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 53281
#define MAXM 150961

int n, m, x;
int u[MAXM], v[MAXM], w[MAXM];
int x_coord[MAXN], y_coord[MAXN];
int edges[MAXM];
int edge_count[MAXN];
int edge_index[MAXM];
int total_cost = 0;

void add_edge(int u, int v, int w) {
    edges[m] = w;
    edge_count[u]++;
    edge_count[v]++;
    edge_index[m] = m;
    m++;
}

int main() {
    scanf("%*d%d%d%d", &n, &m, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x_coord[i], &y_coord[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
        total_cost += w[i];
    }

    int max_cost = 0;
    for (int i = 0; i < m; i++) {
        max_cost = (max_cost > w[i]) ? max_cost : w[i];
    }

    int operations = 0;
    for (int i = 0; i < m; i++) {
        if (w[i] == max_cost) {
            add_edge(u[i], v[i], w[i]);
            operations++;
        }
    }

    printf("%d\n", operations);
    for (int i = 0; i < operations; i++) {
        printf("%d %d %d\n", u[edge_index[i]], v[edge_index[i]], edges[i]);
    }

    return 0;
}