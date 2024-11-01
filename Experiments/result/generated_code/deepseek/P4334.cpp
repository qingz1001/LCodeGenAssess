#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXE 500005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXE * 2];
int head[MAXN], edge_count = 0;
bool visited[MAXN];

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

bool dfs(int u, int target, int blocked_u, int blocked_v) {
    if (u == target) return true;
    visited[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (visited[v]) continue;
        if ((u == blocked_u && v == blocked_v) || (u == blocked_v && v == blocked_u)) continue;
        if (dfs(v, target, blocked_u, blocked_v)) return true;
    }
    return false;
}

int main() {
    int N, E;
    scanf("%d %d", &N, &E);
    for (int i = 1; i <= N; i++) head[i] = -1;
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int A, B, G1, G2;
            scanf("%d %d %d %d", &A, &B, &G1, &G2);
            for (int i = 1; i <= N; i++) visited[i] = false;
            if (dfs(A, B, G1, G2)) printf("yes\n");
            else printf("no\n");
        } else if (type == 2) {
            int A, B, C;
            scanf("%d %d %d", &A, &B, &C);
            for (int i = 1; i <= N; i++) visited[i] = false;
            visited[C] = true;
            if (dfs(A, B, -1, -1)) printf("yes\n");
            else printf("no\n");
        }
    }

    return 0;
}