#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *edges;
    int length;
} Vector;

Vector *graph;
Vector *reverse_graph;
int *indegree;
int *ranks;
int *visit;
int n;

void add_edge(int from, int to) {
    graph[from].edges = (int*)realloc(graph[from].edges, (graph[from].length + 1) * sizeof(int));
    graph[from].edges[graph[from].length++] = to;

    reverse_graph[to].edges = (int*)realloc(reverse_graph[to].edges, (reverse_graph[to].length + 1) * sizeof(int));
    reverse_graph[to].edges[reverse_graph[to].length++] = from;
}

void dfs(int node) {
    visit[node] = 1;
    for (int i = 0; i < graph[node].length; i++) {
        if (!visit[graph[node].edges[i]]) {
            dfs(graph[node].edges[i]);
        }
    }
    ranks[--n] = node;
}

int main() {
    int m, x, y;
    scanf("%d%d", &n, &m);
    graph = (Vector*)malloc((n + 1) * sizeof(Vector));
    reverse_graph = (Vector*)malloc((n + 1) * sizeof(Vector));
    indegree = (int*)calloc(n + 1, sizeof(int));
    ranks = (int*)malloc((n + 1) * sizeof(int));
    visit = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        graph[i].edges = NULL;
        graph[i].length = 0;
        reverse_graph[i].edges = NULL;
        reverse_graph[i].length = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        indegree[y]++;
    }

    int alternative_ranking = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0 && !visit[i]) {
            dfs(i);
            alternative_ranking++;
        }
    }

    if (alternative_ranking > 1) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", ranks[i]);
    }
    printf("\n");

    free(graph);
    free(reverse_graph);
    free(indegree);
    free(ranks);
    free(visit);
    return 0;
}