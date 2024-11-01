#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200001

typedef long long ll;

struct Node {
    ll k, s;
    int r, next;
} node[MAXN * 5];

int head[MAXN], cnt;
int in[MAXN], vis[MAXN];
ll dp[MAXN];

void add(int u, int v, ll k, ll s) {
    node[cnt].k = k;
    node[cnt].s = s;
    node[cnt].r = v;
    node[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = node[i].next) {
        int v = node[i].r;
        dfs(v);
        dp[u] += dp[v];
    }
    dp[u] = (dp[u] < node[u].k) ? node[u].s : dp[u] - node[u].k;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        in[i] = vis[i] = 0;
        dp[i] = 0;
    }
    cnt = 0;

    for (int i = 0; i < n; i++) {
        int r;
        ll k, s;
        scanf("%lld %lld %d", &s, &k, &r);
        add(i, i, k, s);
        for (int j = 0; j < r; j++) {
            int v;
            scanf("%d", &v);
            v--;
            add(i, v, 0, 0);
            in[v]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (in[i] == 0) dfs(i);
    }

    ll ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) ans = (ans < dp[i]) ? ans : dp[i];
    }

    printf("%lld\n", ans);
    return 0;
}