#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int n;
    int *c;
    int s;
} Query;

int N, E, M;
Edge *edges;
Query *queries;
int **adj;

void read_input() {
    scanf("%d %d", &N, &E);
    edges = (Edge *)malloc(E * sizeof(Edge));
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }
    scanf("%d", &M);
    queries = (Query *)malloc(M * sizeof(Query));
    for (int i = 0; i < M; i++) {
        scanf("%d", &queries[i].n);
        queries[i].c = (int *)malloc(queries[i].n * sizeof(int));
        for (int j = 0; j < queries[i].n; j++) {
            scanf("%d", &queries[i].c[j]);
        }
        scanf("%d", &queries[i].s);
    }
}

void build_graph() {
    adj = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        adj[i] = (int *)calloc(N, sizeof(int));
    }
    for (int i = 0; i < E; i++) {
        int u = edges[i].u - 1;
        int v = edges[i].v - 1;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}

int dfs(int u, int parent, int depth, int *visited) {
    visited[u] = 1;
    int max_depth = depth;
    for (int v = 0; v < N; v++) {
        if (adj[u][v] && !visited[v]) {
            int d = dfs(v, u, depth + 1, visited);
            if (d > max_depth) {
                max_depth = d;
            }
        }
    }
    return max_depth;
}

int solve_query(Query q) {
    int *visited = (int *)calloc(N, sizeof(int));
    int max_depth = 0;
    for (int i = 0; i < q.n; i++) {
        int c = q.c[i] - 1;
        memset(visited, 0, N * sizeof(int));
        int depth = dfs(q.s - 1, -1, 0, visited);
        if (depth > max_depth) {
            max_depth = depth;
        }
    }
    free(visited);
    return max_depth;
}

int main() {
    read_input();
    build_graph();
    for (int i = 0; i < M; i++) {
        int result = solve_query(queries[i]);
        printf("%d\n", result);
    }
    for (int i = 0; i < N; i++) {
        free(adj[i]);
    }
    free(adj);
    free(edges);
    for (int i = 0; i < M; i++) {
        free(queries[i].c);
    }
    free(queries);
    return 0;
}