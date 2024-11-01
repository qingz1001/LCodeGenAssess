#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define INF 1e18

typedef long long ll;

struct City {
    int father;
    ll length;
    ll p, q, l;
};

City cities[MAXN];
ll dp[MAXN];

void dfs(int v) {
    if (v == 1) {
        dp[v] = 0;
        return;
    }
    dfs(cities[v].father);
    ll cost = (cities[v].length * cities[v].p + cities[v].q);
    dp[v] = dp[cities[v].father] + cost;
    for (int u = cities[v].father; u != 1; u = cities[u].father) {
        ll total_length = 0;
        int current = v;
        while (current != u) {
            total_length += cities[current].length;
            current = cities[current].father;
        }
        total_length += cities[u].length;
        if (total_length <= cities[v].l) {
            dp[v] = dp[u] + cost;
            break;
        }
    }
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    for (int i = 2; i <= n; i++) {
        scanf("%d %lld %lld %lld %lld", &cities[i].father, &cities[i].length, &cities[i].p, &cities[i].q, &cities[i].l);
    }
    dfs(2);
    for (int i = 2; i <= n; i++) {
        printf("%lld\n", dp[i]);
    }
    return 0;
}