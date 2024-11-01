#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353

typedef struct {
    int v;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} Node;

Node graph[20];
int visited[20];
int depth[20];

void addEdge(int u, int v) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->v = v;
    newEdge->next = graph[u].head;
    graph[u].head = newEdge;

    newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->v = u;
    newEdge->next = graph[v].head;
    graph[v].head = newEdge;
}

void dfs(int u, int d) {
    visited[u] = 1;
    depth[u] = d;
    Edge* edge = graph[u].head;
    while (edge) {
        if (!visited[edge->v]) {
            dfs(edge->v, d + 1);
        }
        edge = edge->next;
    }
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int main() {
    int N, E;
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int n, s;
        scanf("%d", &n);
        int c[n];
        for (int j = 0; j < n; j++) {
            scanf("%d", &c[j]);
        }
        scanf("%d", &s);

        memset(visited, 0, sizeof(visited));
        memset(depth, 0, sizeof(depth));
        dfs(s, 0);

        int maxDepth = 0;
        for (int j = 0; j < n; j++) {
            if (depth[c[j]] > maxDepth) {
                maxDepth = depth[c[j]];
            }
        }

        int r = (maxDepth % MOD) * (modInverse(1, MOD) % MOD) % MOD;
        printf("%d\n", r);
    }

    return 0;
}