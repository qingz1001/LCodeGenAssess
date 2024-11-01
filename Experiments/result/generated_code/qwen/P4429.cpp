#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010

int n, m;
int graph[MAXN][MAXN];
int color_sets[MAXN][2];

void dfs(int node, int parent, int *used_colors) {
    if (graph[node][parent]) {
        return;
    }
    used_colors[color_sets[node][0]] = 1;
    used_colors[color_sets[node][1]] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && i != parent) {
            dfs(i, node, used_colors);
        }
    }
}

int can_color() {
    int used_colors[2] = {0};
    dfs(1, -1, used_colors);
    return used_colors[0] + used_colors[1] >= 2;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &color_sets[i][0], &color_sets[i][1]);
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        if (can_color()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}