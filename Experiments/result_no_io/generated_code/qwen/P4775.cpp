#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001
#define INF 1e18

typedef long long ll;

struct Edge {
    int to;
    ll cost;
};

struct Node {
    int id;
    ll value;
};

int n, m, T;
ll c[MAXN], d[MAXN][MAXN];
Edge edges[MAXN * 2];
Node nodes[MAXN];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %lld", &edges[i].to, &nodes[i].id, &c[i]);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = (i == j) ? 0 : INF;
            }
        }
        for (int i = 1; i <= n; i++) {
            d[i][edges[i].to] = edges[i].cost;
            d[edges[i].to][i] = edges[i].cost;
        }
        floyd();
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %lld", &nodes[i + n].id, &nodes[i + n].value, &nodes[i + n].value);
        }
        ll max_diff = -INF;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                if (i != j) {
                    ll diff = nodes[i].value + nodes[j].value - nodes[i].id * nodes[j].id;
                    if (diff > max_diff) {
                        max_diff = diff;
                    }
                }
            }
        }
        if (max_diff == -INF) {
            printf("F\n");
        } else {
            printf("%lld\n", max_diff);
        }
    }
    return 0;
}