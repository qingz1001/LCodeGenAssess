#include <stdio.h>
#include <string.h>

#define MAX_N 20001
#define MAX_M 20001

int m, n;
int visited[MAX_N];
int graph[MAX_M][MAX_N];
int match[MAX_M];

int dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &m, &n);

        memset(graph, 0, sizeof(graph));
        memset(match, 0, sizeof(match));

        for (int i = 1; i <= m; i++) {
            int k;
            scanf("%d", &k);
            for (int j = 0; j < k; j++) {
                int student;
                scanf("%d", &student);
                graph[i][student] = 1;
            }
        }

        int count = 0;
        for (int i = 1; i <= m; i++) {
            memset(visited, 0, sizeof(visited));
            if (dfs(i)) count++;
        }

        printf("%s\n", count == m ? "YES" : "NO");
    }

    return 0;
}