#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int N, M;
int dp[MAXN];
int max_cities[MAXN];

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];

void add_edge(int from, int to) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->to = to;
    new_edge->next = graph[from];
    graph[from] = new_edge;
}

void dfs(int city) {
    if (dp[city] != -1) return;
    dp[city] = 1;
    max_cities[city] = 0;

    for (Edge* e = graph[city]; e != NULL; e = e->next) {
        int next_city = e->to;
        dfs(next_city);
        if (dp[next_city] + 1 > dp[city]) {
            dp[city] = dp[next_city] + 1;
            max_cities[city] = next_city;
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
    }

    for (int i = 1; i <= N; i++) {
        dp[i] = -1;
    }

    for (int i = 1; i <= N; i++) {
        dfs(i);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", dp[i]);
    }

    for (int i = 1; i <= N; i++) {
        Edge* e = graph[i];
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}