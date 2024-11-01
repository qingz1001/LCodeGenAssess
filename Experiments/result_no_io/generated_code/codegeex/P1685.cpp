#include <stdio.h>
#include <stdlib.h>

#define MOD 10000

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    Edge *edges;
    int *inDegree;
    int *outDegree;
    int *dp;
    int *visited;
} Graph;

Graph *createGraph(int n) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->edges = (Edge *)calloc(n + 1, sizeof(Edge));
    graph->inDegree = (int *)calloc(n + 1, sizeof(int));
    graph->outDegree = (int *)calloc(n + 1, sizeof(int));
    graph->dp = (int *)calloc(n + 1, sizeof(int));
    graph->visited = (int *)calloc(n + 1, sizeof(int));
    return graph;
}

void addEdge(Graph *graph, int from, int to, int weight) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph->edges[from].next;
    graph->edges[from].next = newEdge;
    graph->outDegree[from]++;
    graph->inDegree[to]++;
}

void dfs(Graph *graph, int node) {
    graph->visited[node] = 1;
    for (Edge *edge = graph->edges[node].next; edge != NULL; edge = edge->next) {
        if (!graph->visited[edge->to]) {
            dfs(graph, edge->to);
        }
        graph->dp[node] = (graph->dp[node] + graph->dp[edge->to] + edge->weight) % MOD;
    }
}

int main() {
    int n, m, s, t, t0;
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);

    Graph *graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        addEdge(graph, x, y, t);
    }

    dfs(graph, s);

    int total_time = (graph->dp[t] + t0) % MOD;
    printf("%d\n", total_time);

    free(graph->edges);
    free(graph->inDegree);
    free(graph->outDegree);
    free(graph->dp);
    free(graph->visited);
    free(graph);

    return 0;
}