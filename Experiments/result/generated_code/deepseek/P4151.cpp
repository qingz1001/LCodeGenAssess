#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 50005
#define MAXM 100005

typedef struct {
    int to, next;
    long long weight;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
long long dist[MAXN];
bool visited[MAXN];

void add_edge(int u, int v, long long w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dfs(int u) {
    visited[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        long long w = edges[i].weight;
        if (!visited[v]) {
            dist[v] = dist[u] ^ w;
            dfs(v);
        }
    }
}

long long basis[64];

void insert_vector(long long x) {
    for (int i = 63; i >= 0; i--) {
        if (x & (1LL << i)) {
            if (!basis[i]) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }
}

long long max_xor(long long x) {
    for (int i = 63; i >= 0; i--) {
        if ((x ^ basis[i]) > x) {
            x ^= basis[i];
        }
    }
    return x;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        head[i] = -1;
        visited[i] = false;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1);

    for (int i = 1; i <= N; i++) {
        for (int j = head[i]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            long long w = edges[j].weight;
            insert_vector(dist[i] ^ dist[v] ^ w);
        }
    }

    printf("%lld\n", max_xor(dist[N]));

    return 0;
}