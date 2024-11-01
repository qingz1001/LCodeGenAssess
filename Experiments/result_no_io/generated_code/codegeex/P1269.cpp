#include <stdio.h>
#include <stdlib.h>

#define MAXN 20001

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

Edge *adj[MAXN];
int n;
int initial_signal_strength;

void add_edge(int from, int to, int weight) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = adj[from];
    adj[from] = new_edge;
}

int dfs(int node, int parent) {
    int max_signal_strength = initial_signal_strength;
    int amplifier_count = 0;

    for (Edge *e = adj[node]; e != NULL; e = e->next) {
        if (e->to != parent) {
            int child_amplifier_count = dfs(e->to, node);
            int child_max_signal_strength = max_signal_strength - e->weight;

            if (child_max_signal_strength <= 0) {
                amplifier_count++;
                max_signal_strength = initial_signal_strength;
            } else {
                max_signal_strength = child_max_signal_strength;
            }

            if (child_amplifier_count == -1) {
                return -1;
            }
            amplifier_count += child_amplifier_count;
        }
    }

    return amplifier_count;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
    }

    for (int i = 1; i <= n; i++) {
        int k, to, weight;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d %d", &to, &weight);
            add_edge(i, to, weight);
        }
    }

    scanf("%d", &initial_signal_strength);

    int result = dfs(1, -1);

    if (result == -1) {
        printf("No solution.\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}