#include <stdio.h>
#include <stdlib.h>

#define MAXN 701

int n;
int graph[MAXN][MAXN];
int degree[MAXN];

void dfs(int node, int parent) {
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && i != parent) {
            dfs(i, node);
            degree[node] += degree[i];
        }
    }
    degree[node]++;
}

long long max_score(int node, int parent) {
    long long score = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && i != parent) {
            score *= degree[i];
            score %= 1000000007;
        }
    }
    return score;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    dfs(1, -1);

    printf("%lld\n", max_score(1, -1));

    return 0;
}