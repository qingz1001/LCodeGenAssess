#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define INF 1e18

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    struct Edge *next;
};

struct Node {
    struct Edge *head;
};

struct DSU {
    int parent[MAXN];
    ll cost[MAXN];
    int size[MAXN];
};

void initDSU(struct DSU *dsu, int n) {
    for (int i = 0; i <= n; ++i) {
        dsu->parent[i] = i;
        dsu->cost[i] = 0;
        dsu->size[i] = 1;
    }
}

int find(struct DSU *dsu, int u) {
    if (dsu->parent[u] != u) {
        dsu->parent[u] = find(dsu, dsu->parent[u]);
    }
    return dsu->parent[u];
}

void merge(struct DSU *dsu, int u, int v, ll w) {
    int pu = find(dsu, u);
    int pv = find(dsu, v);
    if (pu == pv) {
        dsu->cost[pu] += w;
        return;
    }
    if (dsu->size[pu] > dsu->size[pv]) {
        std::swap(pu, pv);
    }
    dsu->parent[pu] = pv;
    dsu->size[pv] += dsu->size[pu];
    dsu->cost[pv] += dsu->cost[pu] + w;
}

ll getCost(struct DSU *dsu, int u) {
    return dsu->cost[find(dsu, u)];
}

int main() {
    FILE *in = fopen("center.in", "r");
    FILE *out = fopen("center.out", "w");

    int T;
    fscanf(in, "%d", &T);

    while (T--) {
        int n, m;
        fscanf(in, "%d", &n);
        struct Node nodes[n + 1];
        memset(nodes, 0, sizeof(nodes));

        for (int i = 0; i < n - 1; ++i) {
            int a, b, c;
            fscanf(in, "%d %d %lld", &a, &b, &c);
            struct Edge *e1 = (struct Edge *)malloc(sizeof(struct Edge));
            e1->to = b;
            e1->weight = c;
            e1->next = nodes[a].head;
            nodes[a].head = e1;

            struct Edge *e2 = (struct Edge *)malloc(sizeof(struct Edge));
            e2->to = a;
            e2->weight = c;
            e2->next = nodes[b].head;
            nodes[b].head = e2;
        }

        fscanf(in, "%d", &m);
        struct Edge schemes[m];
        for (int i = 0; i < m; ++i) {
            fscanf(in, "%d %d %lld", &schemes[i].to, &schemes[i].next->to, &schemes[i].weight);
            schemes[i].next = NULL;
        }

        ll max_diff = -INF;
        for (int i = 0; i < m; ++i) {
            struct DSU dsu;
            initDSU(&dsu, n);

            for (int j = 0; j < m; ++j) {
                if (i == j) continue;
                struct Edge *e = schemes[j].head;
                while (e) {
                    merge(&dsu, e->to, e->next->to, e->weight);
                    e = e->next->next;
                }
            }

            struct Edge *e = schemes[i].head;
            while (e) {
                merge(&dsu, e->to, e->next->to, e->weight);
                e = e->next->next;
            }

            ll total_cost = schemes[i].weight;
            for (int j = 1; j <= n; ++j) {
                total_cost += getCost(&dsu, j);
            }

            ll total_value = 0;
            for (int j = 1; j <= n; ++j) {
                total_value += getCost(&dsu, j);
            }

            ll diff = total_value - total_cost;
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        if (max_diff == -INF) {
            fprintf(out, "F\n");
        } else {
            fprintf(out, "%lld\n", max_diff);
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}