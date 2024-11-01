#include <stdio.h>
#include <limits.h>

int n;
int graph[20][20];
int visited[20];
int min_route = INT_MAX;
int route[20];

void dfs(int curr, int distance) {
    if (curr == n) {
        distance += graph[route[curr - 1]][0];
        if (distance < min_route) {
            min_route = distance;
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && graph[route[curr - 1]][i] != 0) {
            visited[i] = 1;
            route[curr] = i;
            dfs(curr + 1, distance + graph[route[curr - 1]][i]);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    visited[0] = 1;
    route[0] = 0;
    dfs(1, 0);

    printf("%d\n", min_route);
    return 0;
}