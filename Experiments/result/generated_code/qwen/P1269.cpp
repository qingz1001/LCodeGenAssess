#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005

typedef struct {
    int to, cost;
} Edge;

int n, edges[MAXN][2], edge_count[MAXN];
int signal_strength, amplifier_count = 0;
int visited[MAXN];

void dfs(int node, int parent) {
    if (visited[node]) return;
    visited[node] = 1;

    for (int i = 0; i < edge_count[node]; ++i) {
        int next = edges[node][2 * i];
        int cost = edges[node][2 * i + 1];
        int new_strength = signal_strength - cost;

        if (new_strength <= 0) {
            amplifier_count++;
            dfs(next, node);
        } else {
            dfs(next, node);
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j) {
            int to, cost;
            scanf("%d %d", &to, &cost);
            edges[i][2 * j] = to - 1;
            edges[i][2 * j + 1] = cost;
            edge_count[i]++;
        }
    }

    scanf("%d", &signal_strength);

    dfs(0, -1);

    if (amplifier_count == 0) {
        printf("No solution.\n");
    } else {
        printf("%d\n", amplifier_count);
    }

    return 0;
}