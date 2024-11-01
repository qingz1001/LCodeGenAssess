#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int node) {
    for (int i = 1; i <= n; ++i) {
        if (graph[node][i] && !visited[i]) {
            visited[i] = 1;
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int b, e;
        scanf("%d %d", &b, &e);
        graph[b][e] = 1;
    }

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            count++;
            dfs(i);
        }
    }

    printf("%d\n", count);

    return 0;
}