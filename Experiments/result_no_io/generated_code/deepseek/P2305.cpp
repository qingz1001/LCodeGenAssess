#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define INF LLONG_MAX

typedef long long ll;

struct City {
    int f; // father city
    ll s; // distance to father city
    ll p, q, l; // ticket parameters and distance limit
    ll min_cost; // minimum cost to reach SZ city
};

City cities[MAXN];
ll dist[MAXN]; // distance from each city to SZ city

void dfs(int v) {
    if (v == 1) {
        cities[v].min_cost = 0;
        return;
    }

    int u = cities[v].f;
    dfs(u);

    ll min_cost = INF;
    ll d = 0;
    for (int w = v; w != 1; w = cities[w].f) {
        d += cities[w].s;
        if (d > cities[v].l) break;
        ll cost = cities[u].min_cost + d * cities[v].p + cities[v].q;
        if (cost < min_cost) min_cost = cost;
    }

    cities[v].min_cost = min_cost;
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    for (int i = 2; i <= n; i++) {
        scanf("%d %lld %lld %lld %lld", &cities[i].f, &cities[i].s, &cities[i].p, &cities[i].q, &cities[i].l);
    }

    for (int i = 2; i <= n; i++) {
        dfs(i);
        printf("%lld\n", cities[i].min_cost);
    }

    return 0;
}