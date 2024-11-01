#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

int n, size[MAXN], parent[MAXN], children[MAXN][MAXN], child_count[MAXN];
double expected_time[MAXN];

void dfs(int u, int p) {
    size[u] = 1;
    parent[u] = p;
    for (int i = 0; i < child_count[u]; ++i) {
        int v = children[u][i];
        dfs(v, u);
        size[u] += size[v];
    }
}

double solve(int u) {
    if (size[u] == 1) return 0;
    double sum = 0;
    for (int i = 0; i < child_count[u]; ++i) {
        int v = children[u][i];
        sum += solve(v);
    }
    expected_time[u] = size[u] + sum / child_count[u];
    return expected_time[u];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        children[a][child_count[a]++] = b;
        children[b][child_count[b]++] = a;
    }

    dfs(0, -1);
    solve(0);

    printf("%.4f\n", expected_time[0]);

    return 0;
}