#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef struct Edge {
    int to, time;
    struct Edge *next;
} Edge;

Edge *edges[MAXN];
int max_time[MAXN], total_time[MAXN];

void add_edge(int from, int to, int time) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = to;
    e->time = time;
    e->next = edges[from];
    edges[from] = e;
}

void dfs(int node, int parent) {
    max_time[node] = 0;
    total_time[node] = 0;

    for (Edge *e = edges[node]; e != NULL; e = e->next) {
        if (e->to == parent) continue;
        dfs(e->to, node);
        if (max_time[e->to] + e->time > max_time[node]) {
            total_time[node] += (max_time[node] - max_time[e->to]) * total_time[e->to];
            max_time[node] = max_time[e->to] + e->time;
        } else {
            total_time[node] += (max_time[e->to] + e->time - max_time[node]) * total_time[e->to];
        }
    }

    total_time[node]++;
}

int main() {
    int N, S, a, b, t;
    scanf("%d %d", &N, &S);

    for (int i = 0; i < N - 1; i++) {
        scanf("%d %d %d", &a, &b, &t);
        add_edge(a, b, t);
        add_edge(b, a, t);
    }

    dfs(S, -1);

    printf("%d\n", total_time[S] - max_time[S]);

    for (int i = 1; i <= N; i++) {
        Edge *e = edges[i];
        while (e != NULL) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}