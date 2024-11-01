#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 50005
#define MAXM 100005

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    struct Edge* next;
};

struct Edge* head[MAXN];
bool visited[MAXN];
ll xor_sum[MAXN];
ll basis[64];

void add_edge(int u, int v, ll w) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = v;
    e->weight = w;
    e->next = head[u];
    head[u] = e;
}

void dfs(int u, ll cur_xor) {
    visited[u] = true;
    xor_sum[u] = cur_xor;
    for (struct Edge* e = head[u]; e != NULL; e = e->next) {
        int v = e->to;
        ll w = e->weight;
        if (!visited[v]) {
            dfs(v, cur_xor ^ w);
        }
    }
}

void insert_basis(ll x) {
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

ll max_xor(ll x) {
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

    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1, 0);

    for (int i = 2; i <= N; i++) {
        insert_basis(xor_sum[i]);
    }

    ll result = max_xor(xor_sum[N]);
    printf("%lld\n", result);

    return 0;
}