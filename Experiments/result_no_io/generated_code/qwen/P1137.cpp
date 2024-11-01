#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

int n, m;
int edges[MAXM][2];
int visited[MAXN];

void dfs(int u) {
    for (int i = 0; i < m; ++i) {
        if (edges[i][1] == u && !visited[edges[i][0]]) {
            visited[edges[i][0]] = 1;
            dfs(edges[i][0]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    int result[MAXN];
    for (int i = 0; i < n; ++i) {
        memset(visited, 0, sizeof(visited));
        visited[i + 1] = 1;
        dfs(i + 1);
        int count = 0;
        for (int j = 1; j <= n; ++j) {
            if (visited[j]) {
                count++;
            }
        }
        result[i] = count;
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", result[i]);
    }

    return 0;
}