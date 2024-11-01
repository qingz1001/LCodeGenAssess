#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXK 300005

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

Edge *newEdge(int to, int weight) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = to;
    e->weight = weight;
    e->next = NULL;
    return e;
}

typedef struct {
    long long max_value;
    int max_edges;
} DP;

DP dp[MAXN][3];
Edge *adj[MAXN];
int N, K;

void addEdge(int from, int to, int weight) {
    Edge *e = newEdge(to, weight);
    e->next = adj[from];
    adj[from] = e;
}

void dfs(int u, int parent) {
    dp[u][0].max_value = 0;
    dp[u][0].max_edges = 0;

    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        dfs(v, u);

        for (int i = 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                if (dp[u][i].max_value < dp[u][j].max_value + dp[v][i-j].max_value + e->weight) {
                    dp[u][i].max_value = dp[u][j].max_value + dp[v][i-j].max_value + e->weight;
                    dp[u][i].max_edges = dp[u][j].max_edges + dp[v][i-j].max_edges;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i < N; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        addEdge(x, y, v);
        addEdge(y, x, v);
    }

    dfs(1, -1);

    long long max_value = LLONG_MIN;
    for (int i = 0; i <= K; i++) {
        if (dp[1][i].max_edges <= K) {
            max_value = (max_value > dp[1][i].max_value) ? max_value : dp[1][i].max_value;
        }
    }

    printf("%lld\n", max_value);

    return 0;
}