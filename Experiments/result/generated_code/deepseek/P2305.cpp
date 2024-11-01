#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define INF LLONG_MAX

typedef long long ll;

struct City {
    int parent;
    ll distance;
    ll p, q, l;
};

struct City cities[MAXN];
ll dp[MAXN];

void dfs(int v, ll dist_so_far, ll cost_so_far) {
    if (v == 1) {
        dp[v] = 0;
        return;
    }

    dp[v] = INF;
    int u = v;
    ll current_dist = 0;

    while (u != 1 && current_dist + cities[u].distance <= cities[v].l) {
        current_dist += cities[u].distance;
        ll new_cost = cost_so_far + current_dist * cities[v].p + cities[v].q;
        if (new_cost < dp[v]) {
            dp[v] = new_cost;
        }
        u = cities[u].parent;
    }

    if (u == 1) {
        return;
    }

    dfs(cities[v].parent, dist_so_far + cities[v].distance, dp[v]);
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);

    for (int i = 2; i <= n; i++) {
        scanf("%d %lld %lld %lld %lld", &cities[i].parent, &cities[i].distance, &cities[i].p, &cities[i].q, &cities[i].l);
    }

    for (int i = 2; i <= n; i++) {
        dfs(i, 0, 0);
        printf("%lld\n", dp[i]);
    }

    return 0;
}