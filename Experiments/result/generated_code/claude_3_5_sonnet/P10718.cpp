#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXK 20
#define MOD 998244353

typedef long long ll;

int n, m, k, q;
int x[MAXN], y[MAXN];
int l[MAXN], C[MAXN][MAXN];
int dp[1 << MAXK];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
    }
    
    for (int i = 0; i < k; i++) {
        scanf("%d", &l[i]);
        for (int j = 0; j < l[i]; j++) {
            scanf("%d", &C[i][j]);
        }
    }
    
    // 初始化dp数组
    dp[0] = 1;
    for (int mask = 1; mask < (1 << k); mask++) {
        int cntBits = __builtin_popcount(mask);
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
                if (dp[mask] >= MOD) dp[mask] -= MOD;
            }
        }
    }
    
    scanf("%d", &q);
    while (q--) {
        int z;
        scanf("%d", &z);
        
        ll ans = 0;
        for (int mask = 0; mask < (1 << k); mask++) {
            if (__builtin_popcount(mask) == z) {
                ans += dp[mask];
            }
        }
        
        printf("%lld\n", ans % MOD);
    }
    
    return 0;
}