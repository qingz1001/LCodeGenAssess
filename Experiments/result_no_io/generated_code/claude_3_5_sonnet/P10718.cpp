#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 300005
#define MOD 998244353

typedef long long ll;

int n, m, k, q;
int x[MAXN], y[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], ecnt;
int cycle[MAXN][MAXN], cycle_size[MAXN];
int dp[1 << 20];

void add_edge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    for (int i = 0; i < k; i++) {
        scanf("%d", &cycle_size[i]);
        for (int j = 0; j < cycle_size[i]; j++) {
            scanf("%d", &cycle[i][j]);
        }
    }
    
    dp[0] = 1;
    for (int mask = 1; mask < (1 << k); mask++) {
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                cnt++;
            }
        }
        dp[mask] = cnt;
    }
    
    scanf("%d", &q);
    while (q--) {
        int z;
        scanf("%d", &z);
        
        ll ans = 0;
        for (int mask = 0; mask < (1 << k); mask++) {
            if (__builtin_popcount(mask) == z) {
                ans = (ans + dp[mask]) % MOD;
            }
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}