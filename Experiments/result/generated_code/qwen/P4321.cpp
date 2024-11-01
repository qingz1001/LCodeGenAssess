#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef struct {
    int to;
    struct Edge* next;
} Edge;

typedef struct {
    int n;
    int* children;
} Node;

int* depth;
int* parent;
Node* nodes;
Edge** edges;
int edge_count;

void add_edge(int u, int v) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->next = edges[u];
    edges[u] = e;
}

void dfs(int node, int prev) {
    depth[node] = depth[prev] + 1;
    parent[node] = prev;
    for (Edge* e = edges[node]; e != NULL; e = e->next) {
        if (e->to == prev) continue;
        dfs(e->to, node);
    }
}

void preprocess(int n) {
    depth = (int*)calloc(n, sizeof(int));
    parent = (int*)calloc(n, sizeof(int));
    nodes = (Node*)calloc(n, sizeof(Node));
    edges = (Edge**)calloc(n, sizeof(Edge*));
    edge_count = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u - 1, v - 1);
        add_edge(v - 1, u - 1);
    }

    dfs(0, 0);
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
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

long long binomial_coefficient(long long n, long long k) {
    long long result = 1;
    for (long long i = 0; i < k; ++i) {
        result = result * (n - i) % MOD;
        result = result * mod_inverse(i + 1, MOD) % MOD;
    }
    return result;
}

int main() {
    int n, e;
    scanf("%d %d", &n, &e);

    preprocess(n);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int n_cities;
        scanf("%d", &n_cities);
        int* cities = (int*)malloc(n_cities * sizeof(int));
        for (int j = 0; j < n_cities; j++) {
            scanf("%d", &cities[j]);
            cities[j]--;
        }
        int s;
        scanf("%d", &s);
        s--;

        long long total = 0;
        for (int j = 0; j < n_cities; j++) {
            int city = cities[j];
            long long path_length = depth[s] + depth[city] - 2 * depth[lca(s, city)];
            total = (total + path_length) % MOD;
        }

        long long expectation = (total * binomial_coefficient(m, n_cities)) % MOD;
        printf("%lld\n", expectation);

        free(cities);
    }

    return 0;
}