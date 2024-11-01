#include <stdio.h>
#include <stdbool.h>

#define MAXN 501

int T, n, m;
int u[MAXN], v[MAXN];
bool graph[MAXN][MAXN];

bool bipartite_coloring(int start, int color) {
    int queue[MAXN * MAXN], front = 0, rear = 0;
    int visited[MAXN] = {0};
    queue[rear++] = start;
    visited[start] = color;

    while (front < rear) {
        int node = queue[front++];
        int node_color = visited[node];

        for (int i = 1; i <= n; i++) {
            if (graph[node][i]) {
                if (!visited[i]) {
                    visited[i] = -node_color;
                    queue[rear++] = i;
                } else if (visited[i] == node_color) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool has_valid_coloring() {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!bipartite_coloring(i, 1)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = false;
            }
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u[i], &v[i]);
            graph[u[i]][v[i]] = true;
            graph[v[i]][u[i]] = true;
        }

        if (has_valid_coloring()) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}