#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int u, v;
    struct Edge *next;
} Edge;

typedef struct {
    int size;
    Edge **edges;
} Graph;

Graph *createGraph(int n) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->size = n;
    graph->edges = (Edge **)malloc(n * sizeof(Edge *));
    for (int i = 0; i < n; i++) {
        graph->edges[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int u, int v) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->u = u;
    edge->v = v;
    edge->next = graph->edges[u];
    graph->edges[u] = edge;
    edge = (Edge *)malloc(sizeof(Edge));
    edge->u = v;
    edge->v = u;
    edge->next = graph->edges[v];
    graph->edges[v] = edge;
}

int main() {
    int n, e, q;
    scanf("%d %d", &n, &e);

    Graph *graph = createGraph(n);

    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        addEdge(graph, u, v);
    }

    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int A, B, G1, G2;
            scanf("%d %d %d %d", &A, &B, &G1, &G2);
            A--; B--; G1--; G2--;
            // Implement logic for query type 1
        } else if (type == 2) {
            int A, B, C;
            scanf("%d %d %d", &A, &B, &C);
            A--; B--; C--;
            // Implement logic for query type 2
        }
    }

    return 0;
}