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

void add_edge(int u, int v) {
    edges[edge_count].to = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;

    edges[edge_count].to = u;
    edges[edge_count].next = head[v];
    head[v] = edge_count++;
}

bool visited[MAXN];

void dfs(int u) {
    visited[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!visited[v]) {
            dfs(v);
        }
    }
}

bool can_reach(int start, int end) {
    for (int i = 1; i <= N; i++) {
        visited[i] = false;
    }
    dfs(start);
    return visited[end];
}

int main() {
    int N, E;
    scanf("%d %d", &N, &E);

    for (int i = 1; i <= N; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    int Q;
    scanf("%d", &Q);

    for (int q = 0; q < Q; q++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int A, B, G1, G2;
            scanf("%d %d %d %d", &A, &B, &G1, &G2);

            // Temporarily remove the edge G1-G2
            for (int i = head[G1]; i != -1; i = edges[i].next) {
                if (edges[i].to == G2) {
                    edges[i].to = -1;
                    break;
                }
            }
            for (int i = head[G2]; i != -1; i = edges[i].next) {
                if (edges[i].to == G1) {
                    edges[i].to = -1;
                    break;
                }
            }

            bool reachable = can_reach(A, B);

            // Restore the edge G1-G2
            for (int i = head[G1]; i != -1; i = edges[i].next) {
                if (edges[i].to == -1) {
                    edges[i].to = G2;
                    break;
                }
            }
            for (int i = head[G2]; i != -1; i = edges[i].next) {
                if (edges[i].to == -1) {
                    edges[i].to = G1;
                    break;
                }
            }

            printf("%s\n", reachable ? "yes" : "no");
        } else if (type == 2) {
            int A, B, C;
            scanf("%d %d %d", &A, &B, &C);

            bool reachable = can_reach(A, B);
            printf("%s\n", reachable ? "yes" : "no");
        }
    }

    return 0;
}