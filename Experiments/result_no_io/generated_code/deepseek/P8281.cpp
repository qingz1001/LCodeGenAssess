#include <stdio.h>
#include <stdbool.h>

#define MAXN 50
#define MAXM 2500

int n, m;
bool graph[MAXN][MAXN];
bool visited[MAXN];
int path[MAXN];

void dfs(int pos, int depth) {
    if (depth == n) {
        if (graph[pos][0]) {
            for (int i = 0; i < n; i++) {
                printf("%d ", path[i] + 1);
            }
            printf("1\n");
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[pos][i]) {
            visited[i] = true;
            path[depth] = i;
            dfs(i, depth + 1);
            visited[i] = false;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u - 1][v - 1] = true;
    }

    visited[0] = true;
    path[0] = 0;
    dfs(0, 1);

    return 0;
}