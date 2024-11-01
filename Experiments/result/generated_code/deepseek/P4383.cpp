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
    long long value;
    int size;
} Pair;

Pair max(Pair a, Pair b) {
    return a.value > b.value ? a : b;
}

Pair add(Pair a, Pair b) {
    return (Pair){a.value + b.value, a.size + b.size};
}

Pair dp[MAXN][3];
Edge *adj[MAXN];
int N, K;

void addEdge(int u, int v, int w) {
    Edge *e1 = newEdge(v, w);
    e1->next = adj[u];
    adj[u] = e1;

    Edge *e2 = newEdge(u, w);
    e2->next = adj[v];
    adj[v] = e2;
}

void dfs(int u, int parent) {
    dp[u][0] = (Pair){0, 0};
    dp[u][1] = (Pair){INT_MIN, 0};
    dp[u][2] = (Pair){INT_MIN, 0};

    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v == parent) continue;
        dfs(v, u);

        Pair dp0 = dp[u][0], dp1 = dp[u][1], dp2 = dp[u][2];

        dp[u][2] = max(dp[u][2], add(dp2, dp[v][0]));
        dp[u][2] = max(dp[u][2], add(dp1, add(dp[v][1], (Pair){e->weight, 1})));

        dp[u][1] = max(dp[u][1], add(dp1, dp[v][0]));
        dp[u][1] = max(dp[u][1], add(dp0, add(dp[v][1], (Pair){e->weight, 1})));

        dp[u][0] = max(dp[u][0], add(dp0, dp[v][0]));
    }
}

int main() {
    scanf("%d %d", &N, &K);
    K++; // We need to add K edges, so we need to cut K+1 edges

    for (int i = 1; i < N; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        addEdge(x, y, v);
    }

    dfs(1, -1);

    Pair result = dp[1][0];
    for (int i = 1; i <= N; i++) {
        result = max(result, dp[i][K]);
    }

    printf("%lld\n", result.value);

    return 0;
}