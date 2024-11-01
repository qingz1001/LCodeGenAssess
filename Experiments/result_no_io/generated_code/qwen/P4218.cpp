#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 50005

int n, m;
char eigen[M + 1];
char materials[MAXN];
int graph[MAXN][MAXN];
int visited[MAXN];
int parent[MAXN];
int path[MAXN];

void dfs(int u) {
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && !visited[v]) {
            parent[v] = u;
            dfs(v);
        }
    }
}

int find_path(int start, int end) {
    memset(visited, 0, sizeof(visited));
    dfs(start);
    if (!visited[end]) return -1;

    int len = 0;
    while (end != -1) {
        path[len++] = end;
        end = parent[end];
    }

    for (int i = len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return len;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
        graph[y][x] = 1;
    }
    scanf("%s", materials);
    scanf("%s", eigen);

    int total_expectation = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int len = find_path(i, j);
            if (len == -1) continue;
            int k = 0;
            int count = 0;
            while (k < len) {
                char sub[m + 1];
                strncpy(sub, eigen + k, m);
                sub[m] = '\0';
                if (strncmp(materials + path[k] - 1, sub, m) == 0) {
                    count++;
                }
                k += m;
            }
            total_expectation += count;
        }
    }

    printf("%d\n", total_expectation * n * n / (n * n));

    return 0;
}