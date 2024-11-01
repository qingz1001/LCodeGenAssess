#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20000

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAXN];
    int count;
} Node;

Node nodes[MAXN];
int visited[MAXN];
int amplifier_count = 0;
int signal_strength;

void add_edge(int from, int to, int weight) {
    nodes[from].edges[nodes[from].count].to = to;
    nodes[from].edges[nodes[from].count].weight = weight;
    nodes[from].count++;
}

int dfs(int node, int strength) {
    visited[node] = 1;
    if (strength <= 0) {
        return 0;
    }
    int need_amplifier = 0;
    for (int i = 0; i < nodes[node].count; i++) {
        int next = nodes[node].edges[i].to;
        int weight = nodes[node].edges[i].weight;
        if (!visited[next]) {
            if (strength - weight <= 0) {
                need_amplifier = 1;
            }
            if (dfs(next, strength - weight) == 0) {
                need_amplifier = 1;
            }
        }
    }
    if (need_amplifier) {
        amplifier_count++;
        return signal_strength;
    }
    return strength;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int to, weight;
            scanf("%d %d", &to, &weight);
            add_edge(i, to, weight);
        }
    }
    scanf("%d", &signal_strength);

    int result = dfs(1, signal_strength);
    if (result > 0) {
        printf("%d\n", amplifier_count);
    } else {
        printf("No solution.\n");
    }

    return 0;
}