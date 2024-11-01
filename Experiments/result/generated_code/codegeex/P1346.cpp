#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int graph[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];

void dfs(int n, int start, int end) {
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    visited[start] = 1;
    while (1) {
        int min_dist = MAXN;
        int min_node = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                min_node = i;
            }
        }
        if (min_node == -1) break;
        visited[min_node] = 1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (graph[min_node][i] == 1 || graph[i][min_node] == 1)) {
                if (dist[min_node] + 1 < dist[i]) {
                    dist[i] = dist[min_node] + 1;
                }
            }
        }
    }
}

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
        for (int j = 0; j < k; j++) {
            int x;
            scanf("%d", &x);
            graph[i][x-1] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        dist[i] = MAXN;
    }
    dfs(n, a-1, b-1);
    if (dist[b-1] == MAXN) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[b-1]);
    }
    return 0;
}