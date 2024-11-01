#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define INF 0x3f3f3f3f

int graph[MAXN][MAXN];
int dist[MAXN];
bool visited[MAXN];

void dfs(int n, int start, int end) {
    if (start == end) {
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (graph[start][i] && !visited[i]) {
            visited[i] = true;
            dist[i] = dist[start] + 1;
            dfs(n, i, end);
        }
    }
}

int main() {
    int n, start, end;
    scanf("%d%d%d", &n, &start, &end);

    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        if (k > 0) {
            for (int j = 0; j < k; j++) {
                int v;
                scanf("%d", &v);
                graph[i][v] = 1;
            }
        }
    }

    memset(dist, INF, sizeof(dist));
    memset(visited, false, sizeof(visited));

    visited[start] = true;
    dist[start] = 0;

    dfs(n, start, end);

    if (dist[end] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[end]);
    }

    return 0;
}