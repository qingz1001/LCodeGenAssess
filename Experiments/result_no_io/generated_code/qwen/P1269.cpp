#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005

typedef struct {
    int to, cost;
} Edge;

Edge edges[MAXN * 2];
int degree[MAXN], parent[MAXN], visited[MAXN];
int n, signal_strength;

void dfs(int node, int strength) {
    if (strength <= 0) return;
    visited[node] = 1;
    for (int i = 0; i < degree[node]; i++) {
        int next = edges[i].to;
        if (!visited[next]) {
            dfs(next, strength - edges[i].cost);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int to, cost;
            scanf("%d %d", &to, &cost);
            edges[degree[i]] = (Edge){to, cost};
            edges[degree[to]] = (Edge){i, cost};
            degree[i]++;
            degree[to]++;
        }
    }
    scanf("%d", &signal_strength);

    int amplifier_count = 0;
    for (int i = 2; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, signal_strength);
            amplifier_count++;
        }
    }

    if (amplifier_count == n - 1) {
        printf("No solution.\n");
    } else {
        printf("%d\n", amplifier_count);
    }

    return 0;
}