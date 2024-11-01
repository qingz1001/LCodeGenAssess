#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 100005

typedef long long ll;

int n, m;
ll d[MAXM];
int head[MAXN], to[MAXM << 1], next[MAXM << 1], edge_cnt;

void add_edge(int u, int v, ll w) {
    to[edge_cnt] = v, next[edge_cnt] = head[u], d[edge_cnt] = w, head[u] = edge_cnt++;
}

ll dp[1 << 20];

void dfs(int u, int fa) {
    for (int i = head[u]; ~i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        for (int j = (1 << 20) - 1; j >= 0; --j) {
            if ((dp[j] ^ d[i]) < dp[j]) continue;
            dp[j ^ d[i]] |= dp[j];
        }
    }
    dp[d[u]] |= 1;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs(1, -1);
    ll ans = 0;
    for (int i = 0; i < (1 << 20); ++i) {
        ans = (ans > dp[i] ? ans : dp[i]);
    }
    printf("%lld\n", ans);
    return 0;
}