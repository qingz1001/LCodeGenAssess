#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

typedef struct {
    int to;
    struct Edge* next;
} Edge;

typedef struct {
    int size;
    Edge** edges;
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = n + 1;
    graph->edges = (Edge**)malloc((n + 1) * sizeof(Edge*));
    for (int i = 1; i <= n; i++) {
        graph->edges[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int from, int to) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = to;
    edge->next = graph->edges[from];
    graph->edges[from] = edge;
}

int dfs(int node, int parent, int* weights, int* max_value, int* total_sum, Graph* graph) {
    int sum = 0;
    for (Edge* e = graph->edges[node]; e != NULL; e = e->next) {
        if (e->to == parent) continue;
        int child_sum = dfs(e->to, node, weights, max_value, total_sum, graph);
        sum += child_sum;
        *max_value = (*max_value > child_sum * weights[node]) ? *max_value : child_sum * weights[node];
        *total_sum = (*total_sum + child_sum * weights[node]) % MOD;
    }
    return sum + weights[node];
}

int main() {
    int n;
    scanf("%d", &n);
    Graph* graph = createGraph(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
        addEdge(graph, v, u);
    }
    int* weights = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weights[i]);
    }

    int max_value = 0;
    int total_sum = 0;
    dfs(1, 0, weights, &max_value, &total_sum, graph);

    printf("%d %d\n", max_value, total_sum);

    free(weights);
    for (int i = 1; i <= n; i++) {
        Edge* e = graph->edges[i];
        while (e != NULL) {
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
    }
    free(graph->edges);
    free(graph);

    return 0;
}