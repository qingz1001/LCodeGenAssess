#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 16000

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

Edge *graph[MAXN + 1];
int beauty[MAXN + 1];
int dp[MAXN + 1][2];

void add_edge(int u, int v) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v;
    e->next = graph[u];
    graph[u] = e;
}

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = beauty[u];

    for (Edge *e = graph[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += dp[v][1];
        dp[u][1] += dp[v][0];
    }

    if (dp[u][0] < dp[u][1]) {
        dp[u][0] = dp[u][1];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &beauty[i]);
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }

    dfs(1, -1);

    int max_beauty = dp[1][0];
    printf("%d\n", max_beauty);

    for (int i = 1; i <= n; i++) {
        for (Edge *e = graph[i]; e != NULL; ) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}