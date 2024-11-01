#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 200000
#define MAXQ 1000000

typedef struct {
    int v, w, r;
} Edge;

typedef struct {
    int node;
    double voltage;
} VoltageSource;

typedef struct {
    int a, b;
} Query;

int n, m, k, q;
Edge edges[MAXM];
VoltageSource voltageSources[MAXN];
Query queries[MAXQ];
double voltages[MAXN];

void solve() {
    // Initialize voltages
    for (int i = 0; i <= n; i++) {
        voltages[i] = 0.0;
    }

    // Set voltages for the voltage sources
    for (int i = 0; i < k; i++) {
        voltages[voltageSources[i].node] = voltageSources[i].voltage;
    }

    // Apply the voltage drop across resistors
    for (int i = 0; i < m; i++) {
        int v = edges[i].v;
        int w = edges[i].w;
        int r = edges[i].r;
        if (voltages[v] != 0.0 && voltages[w] == 0.0) {
            voltages[w] = voltages[v] - (voltages[v] - voltages[0]) * (double)r / (double)(r + voltages[v]);
        } else if (voltages[w] != 0.0 && voltages[v] == 0.0) {
            voltages[v] = voltages[w] - (voltages[w] - voltages[0]) * (double)r / (double)(r + voltages[w]);
        }
    }

    // Answer the queries
    for (int i = 0; i < q; i++) {
        int a = queries[i].a;
        int b = queries[i].b;
        double result = voltages[a] - voltages[b];
        printf("%.2f\n", result);
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 0; i < k; i++) {
        scanf("%d %lf", &voltageSources[i].node, &voltageSources[i].voltage);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].v, &edges[i].w, &edges[i].r);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i].a, &queries[i].b);
    }

    solve();

    return 0;
}