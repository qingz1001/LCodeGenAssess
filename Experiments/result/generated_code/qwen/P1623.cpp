#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n;
int tree[MAXN][MAXN];
int degree[MAXN];
int match[MAXN];
int visited[MAXN];

int dfs(int u) {
    for (int v = 1; v <= n; ++v) {
        if (!visited[v] && tree[u][v]) {
            visited[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[u] = v;
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int u, m;
        scanf("%d %d", &u, &m);
        for (int j = 0; j < m; ++j) {
            int v;
            scanf("%d", &v);
            tree[u][v] = 1;
            degree[u]++;
        }
    }

    int max_match = 0;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] > 0) {
            memset(visited, 0, sizeof(visited));
            if (dfs(i)) {
                max_match++;
            }
        }
    }

    printf("%d\n", max_match);

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (match[i] != -1 && match[match[i]] == i) {
            count++;
        }
    }

    printf("%d\n", count / 2);

    return 0;
}