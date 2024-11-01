#include <stdio.h>
#include <stdlib.h>

#define MAXN 10010
#define MAXM 20010

int T, n, m;
int graph[MAXN][MAXN];
int degree[MAXN];
int visited[MAXN];

void dfs(int node) {
    visited[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            degree[i] = 0;
            for (int j = 1; j <= n; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
            degree[u]++;
            degree[v]++;
        }

        int oddDegree = 0;
        for (int i = 1; i <= n; i++) {
            if (degree[i] % 2 != 0) {
                oddDegree++;
            }
        }

        if (oddDegree > 2) {
            printf("NO\n");
            continue;
        }

        int connectedComponents = 0;
        for (int i = 1; i <= n; i++) {
            visited[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i);
                connectedComponents++;
            }
        }

        if (connectedComponents == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}