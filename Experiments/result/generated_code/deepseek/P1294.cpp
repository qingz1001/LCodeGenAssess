#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
#define MAXM 50

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];
int max_distance = 0;

void dfs(int current, int distance) {
    if (distance > max_distance) {
        max_distance = distance;
    }
    for (int i = 0; i < n; i++) {
        if (graph[current][i] > 0 && !visited[i]) {
            visited[i] = 1;
            dfs(i, distance + graph[current][i]);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u-1][v-1] = w;
        graph[v-1][u-1] = w;
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 1;
        dfs(i, 0);
        visited[i] = 0;
    }

    printf("%d\n", max_distance);
    return 0;
}