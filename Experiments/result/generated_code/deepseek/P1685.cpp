#include <stdio.h>
#include <stdlib.h>

#define MOD 10000

typedef struct Edge {
    int to;
    int time;
    struct Edge* next;
} Edge;

typedef struct Node {
    Edge* head;
} Node;

Node graph[10001];
int dp[10001];
int visited[10001];
int n, m, s, t, t0;

void addEdge(int from, int to, int time) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->time = time;
    newEdge->next = graph[from].head;
    graph[from].head = newEdge;
}

void dfs(int node) {
    visited[node] = 1;
    for (Edge* e = graph[node].head; e != NULL; e = e->next) {
        if (!visited[e->to]) {
            dfs(e->to);
        }
        dp[node] = (dp[node] + dp[e->to] + e->time) % MOD;
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);
    for (int i = 0; i < m; i++) {
        int x, y, time;
        scanf("%d %d %d", &x, &y, &time);
        addEdge(x, y, time);
    }

    dp[t] = 0;
    dfs(s);

    int total = dp[s];
    for (int i = 1; i <= n; i++) {
        if (i != s && i != t) {
            total = (total + dp[i]) % MOD;
        }
    }
    total = (total + t0) % MOD;

    printf("%d\n", total);

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        Edge* e = graph[i].head;
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}