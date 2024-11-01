#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define INF 1LL << 60

typedef long long ll;

struct Node {
    int father;
    ll distance;
    ll p, q;
    ll l;
};

Node nodes[MAXN];
ll dp[MAXN];

void dfs(int u, int parent) {
    dp[u] = INF;
    for (int v = u; v != -1; v = nodes[v].father) {
        if (nodes[v].distance > nodes[v].l)
            break;
        ll cost = nodes[v].distance * nodes[v].p + nodes[v].q;
        dp[u] = dp[u] < cost ? dp[u] : cost;
    }
    if (parent != -1) {
        dp[u] = dp[u] < dp[parent] + nodes[u].distance * nodes[u].p + nodes[u].q ? dp[u] : dp[parent] + nodes[u].distance * nodes[u].p + nodes[u].q;
    }
}

int main() {
    int n, t;
    scanf("%d %d", &n, &t);
    for (int i = 2; i <= n; ++i) {
        scanf("%d %lld %lld %lld %lld", &nodes[i].father, &nodes[i].distance, &nodes[i].p, &nodes[i].q, &nodes[i].l);
        nodes[i].father--;
    }
    for (int i = 2; i <= n; ++i) {
        dfs(i, -1);
    }
    for (int i = 2; i <= n; ++i) {
        printf("%lld\n", dp[i]);
    }
    return 0;
}