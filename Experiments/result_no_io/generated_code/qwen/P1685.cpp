#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MOD 10000

typedef struct {
    int to, weight;
} Edge;

int n, m, s, t, t0;
Edge edges[MAXN];
int visited[MAXN];

void dfs(int u, int depth, int *count, int *time) {
    if (u == t) {
        (*count)++;
        (*time) = (*time + depth - 1) % MOD;
        return;
    }
    for (int i = 0; i < m; i++) {
        if (edges[i].from == u && !visited[i]) {
            visited[i] = 1;
            dfs(edges[i].to, depth + edges[i].weight, count, time);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    int count = 0, total_time = 0;
    dfs(s, 0, &count, &total_time);

    printf("%d\n", (total_time + count * t0) % MOD);

    return 0;
}