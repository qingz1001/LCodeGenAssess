#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXE 500005

typedef struct {
    int u, v;
} Edge;

Edge edges[MAXE];
int parent[MAXN], rank[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;
    if (rank[px] > rank[py]) {
        parent[py] = px;
    } else if (rank[px] < rank[py]) {
        parent[px] = py;
    } else {
        parent[py] = px;
        rank[px]++;
    }
}

int main() {
    int N, E, Q;
    scanf("%d %d", &N, &E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
        edges[i].u--;
        edges[i].v--;
    }
    scanf("%d", &Q);

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < E; i++) {
        union_set(edges[i].u, edges[i].v);
    }

    while (Q--) {
        int type, A, B, G1, G2, C;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d %d", &A, &B, &G1, &G2);
            A--; B--; G1--; G2--;
            int original = find(A);
            union_set(G1, G2);
            int result = find(A) != find(B) ? "yes" : "no";
            union_set(original, A);
            printf("%s\n", result);
        } else {
            scanf("%d %d %d", &A, &B, &C);
            A--; B--; C--;
            int original = find(A);
            for (int i = 0; i < E; i++) {
                if (edges[i].u == C || edges[i].v == C) {
                    union_set(edges[i].u, edges[i].v);
                }
            }
            int result = find(A) != find(B) ? "yes" : "no";
            for (int i = 0; i < E; i++) {
                if (edges[i].u == C || edges[i].v == C) {
                    union_set(edges[i].u, edges[i].v);
                }
            }
            union_set(original, A);
            printf("%s\n", result);
        }
    }

    return 0;
}