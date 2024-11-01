#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

typedef struct {
    int to, next;
    long long w;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_cnt = 0;

void add_edge(int u, int v, long long w) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].w = w;
    head[u] = edge_cnt++;
}

long long max_xor(long long a, long long b) {
    return a ^ b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int S, T;
        long long D;
        scanf("%d %d %lld", &S, &T, &D);
        add_edge(S - 1, T - 1, D);
        add_edge(T - 1, S - 1, D);
    }

    // Your code here

    return 0;
}