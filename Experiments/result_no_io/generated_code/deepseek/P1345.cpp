#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 101
#define MAXM 601

int N, M, c1, c2;
int graph[MAXN][MAXN];
int visited[MAXN];
int minCut = INT_MAX;

int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int u, int v, int cut) {
    if (u == v) {
        minCut = min(minCut, cut);
        return;
    }
    visited[u] = 1;
    for (int i = 1; i <= N; i++) {
        if (graph[u][i] && !visited[i]) {
            dfs(i, v, cut + (i != c1 && i != c2));
        }
    }
    visited[u] = 0;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &c1, &c2);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    dfs(c1, c2, 0);

    printf("%d\n", minCut);

    return 0;
}