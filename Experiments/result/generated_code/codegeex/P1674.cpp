#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 205
#define MAXP 40005

int n, p, t;
int dist[MAXN][MAXN];
int visited[MAXN];
int max_path[MAXP];

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void dfs(int node, int depth, int max_length) {
    if (node == n) {
        max_path[depth] = max_length;
        return;
    }
    visited[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[node][i] > 0 && !visited[i]) {
            dfs(i, depth + 1, (max_length > dist[node][i]) ? max_length : dist[node][i]);
        }
    }
    visited[node] = 0;
}

int main() {
    scanf("%d %d %d", &n, &p, &t);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = 0;
        }
    }
    for (int i = 0; i < p; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        dist[a][b] = l;
        dist[b][a] = l;
    }
    memset(visited, 0, sizeof(visited));
    dfs(1, 0, 0);
    qsort(max_path, t + 1, sizeof(int), compare);
    printf("%d\n", max_path[t]);
    return 0;
}