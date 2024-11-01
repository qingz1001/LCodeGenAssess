#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20000

typedef struct Edge {
    int to, weight;
    struct Edge* next;
} Edge;

Edge* graph[MAXN + 1];
int amplifier_count = 0;
int signal_strength;

void add_edge(int from, int to, int weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->weight = weight;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

int dfs(int node, int parent, int current_strength) {
    int needed_amplifiers = 0;
    Edge* edge = graph[node];
    while (edge != NULL) {
        if (edge->to != parent) {
            int new_strength = current_strength - edge->weight;
            if (new_strength <= 0) {
                needed_amplifiers++;
                new_strength = signal_strength - edge->weight;
            }
            needed_amplifiers += dfs(edge->to, node, new_strength);
        }
        edge = edge->next;
    }
    return needed_amplifiers;
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
            add_edge(to, i, weight);
        }
    }

    scanf("%d", &signal_strength);

    amplifier_count = dfs(1, -1, signal_strength);

    if (amplifier_count == 0) {
        printf("No solution.\n");
    } else {
        printf("%d\n", amplifier_count);
    }

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        Edge* edge = graph[i];
        while (edge != NULL) {
            Edge* next = edge->next;
            free(edge);
            edge = next;
        }
    }

    return 0;
}