#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int p[MAXN];
int graph[MAXN][MAXN];
double k;

void dfs(int node, int parent, double *profit) {
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && i != parent) {
            dfs(i, node, profit);
            *profit += p[i] * k;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    scanf("%lf", &k);

    double total_profit = 0;
    dfs(0, -1, &total_profit);

    printf("%.1f\n", total_profit);

    return 0;
}