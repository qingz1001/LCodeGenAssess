#include <stdio.h>
#include <stdlib.h>

#define MAXN 205
#define EPS 1e-9

int n, m, k, q;
double u[MAXN];
double adj[MAXN][MAXN];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            adj[i][j] = 0;
        }
    }
}

void add_edge(int v, int w, double r) {
    adj[v][w] += r;
    adj[w][v] += r;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        if (adj[i][0] > 0) {
            printf("%.2f\n", u[0] - u[i]);
        } else {
            printf("0.00\n");
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);
    init();
    for (int i = 1; i <= k; ++i) {
        int x, y;
        double z;
        scanf("%d %d %lf", &x, &y, &z);
        u[x] = z;
    }
    for (int i = 1; i <= m; ++i) {
        int v, w;
        double r;
        scanf("%d %d %lf", &v, &w, &r);
        add_edge(v, w, r);
    }
    solve();
    return 0;
}