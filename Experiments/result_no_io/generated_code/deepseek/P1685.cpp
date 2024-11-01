#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10000

typedef struct Edge {
    int to;
    int time;
    struct Edge* next;
} Edge;

typedef struct Node {
    Edge* head;
    int total_time;
} Node;

Node graph[10001];
int visited[10001];
int n, m, s, t, t0;

void add_edge(int from, int to, int time) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->time = time;
    new_edge->next = graph[from].head;
    graph[from].head = new_edge;
}

void dfs(int node, int current_time) {
    if (node == t) {
        graph[node].total_time = (graph[node].total_time + current_time) % MOD;
        return;
    }

    visited[node] = 1;
    Edge* edge = graph[node].head;
    while (edge) {
        if (!visited[edge->to]) {
            dfs(edge->to, (current_time + edge->time) % MOD);
        }
        edge = edge->next;
    }
    visited[node] = 0;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);

    for (int i = 1; i <= n; i++) {
        graph[i].head = NULL;
        graph[i].total_time = 0;
    }

    for (int i = 0; i < m; i++) {
        int x, y, time;
        scanf("%d %d %d", &x, &y, &time);
        add_edge(x, y, time);
    }

    dfs(s, 0);

    int total_time = graph[t].total_time;
    for (int i = 1; i <= n; i++) {
        Edge* edge = graph[i].head;
        while (edge) {
            Edge* next = edge->next;
            free(edge);
            edge = next;
        }
    }

    printf("%d\n", total_time);

    return 0;
}