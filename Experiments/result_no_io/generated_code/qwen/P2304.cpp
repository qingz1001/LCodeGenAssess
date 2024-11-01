#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int n;
int x[MAXN], y[MAXN];
int visited[MAXN];

void dfs(int u, int dir, int *count, int path[]) {
    if (visited[u]) return;
    visited[u] = 1;
    path[*count] = u;
    (*count)++;
    int dx[5] = {0, 0, -1, 1, -1};
    int dy[5] = {-1, 1, -1, 1, 0};
    for (int i = 0; i < 5; i++) {
        int nx = x[u] + dx[i];
        int ny = y[u] + dy[i];
        if (nx >= 0 && nx <= 1000 && ny >= 0 && ny <= 1000) {
            dfs(nx, i, count, path);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    int max_count = 0;
    int path[MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memset(visited, 0, sizeof(visited));
            int count = 0;
            dfs(i, j, &count, path);
            if (count > max_count) {
                max_count = count;
            }
        }
    }

    printf("%d\n", max_count);
    for (int i = 0; i < max_count; i++) {
        printf("%d ", path[i] + 1);
    }
    printf("\n");

    int roads = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = abs(x[i] - x[j]);
            int dy = abs(y[i] - y[j]);
            if (dx != dy) {
                roads++;
            }
        }
    }
    printf("%d\n", roads);

    return 0;
}