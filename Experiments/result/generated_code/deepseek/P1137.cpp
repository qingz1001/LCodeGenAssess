#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int dp[MAXN];

void addEdge(int x, int y) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = y;
    newEdge->next = adj[x];
    adj[x] = newEdge;
}

void dfs(int u) {
    if (dp[u] != 0) return;
    dp[u] = 1;
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        dfs(v);
        if (dp[v] + 1 > dp[u]) {
            dp[u] = dp[v] + 1;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(x, y);
    }

    for (int i = 1; i <= N; i++) {
        dfs(i);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", dp[i]);
    }

    // Free allocated memory
    for (int i = 1; i <= N; i++) {
        Edge* e = adj[i];
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }

    return 0;
}