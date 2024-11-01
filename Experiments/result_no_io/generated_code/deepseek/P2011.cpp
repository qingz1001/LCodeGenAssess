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

int n, m, k, q;
Edge edges[MAXM];
VoltageSource sources[MAXN];
int queries[MAXQ][2];
double voltages[MAXN];

void solve() {
    // Initialize voltages
    for (int i = 0; i < n; i++) {
        voltages[i] = 0.0;
    }

    // Apply voltage sources
    for (int i = 0; i < k; i++) {
        voltages[sources[i].node] = sources[i].voltage;
    }

    // Apply Ohm's law to calculate voltages at other nodes
    for (int i = 0; i < m; i++) {
        int v = edges[i].v;
        int w = edges[i].w;
        int r = edges[i].r;
        double deltaV = voltages[v] - voltages[w];
        if (deltaV != 0) {
            double current = deltaV / r;
            voltages[v] -= current * r;
            voltages[w] += current * r;
        }
    }

    // Answer queries
    for (int i = 0; i < q; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        double result = voltages[a] - voltages[b];
        printf("%.2f\n", result);
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 0; i < k; i++) {
        scanf("%d %lf", &sources[i].node, &sources[i].voltage);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].v, &edges[i].w, &edges[i].r);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    solve();

    return 0;
}