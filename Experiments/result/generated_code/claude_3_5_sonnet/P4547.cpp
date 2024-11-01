#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 15
#define MAXM 225

typedef long long ll;

int n, m;
int t[MAXM], a1[MAXM], b1[MAXM], a2[MAXM], b2[MAXM];
ll dp[1 << MAXN][1 << MAXN];
ll inv2;

ll quick_pow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

void add(ll *x, ll y) {
    *x += y;
    if (*x >= MOD) *x -= MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &t[i], &a1[i], &b1[i]);
        a1[i]--; b1[i]--;
        if (t[i]) {
            scanf("%d%d", &a2[i], &b2[i]);
            a2[i]--; b2[i]--;
        }
    }

    inv2 = quick_pow(2, MOD - 2);
    dp[0][0] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int s1 = (1 << n) - 1; s1 >= 0; s1--) {
            for (int s2 = (1 << n) - 1; s2 >= 0; s2--) {
                ll &cur = dp[s1][s2];
                if (cur == 0) continue;
                
                if (t[i] == 0) {
                    add(&dp[s1 | (1 << a1[i])][s2 | (1 << b1[i])], cur * inv2 % MOD);
                } else if (t[i] == 1) {
                    add(&dp[s1 | (1 << a1[i]) | (1 << a2[i])][s2 | (1 << b1[i]) | (1 << b2[i])], cur * inv2 % MOD);
                } else {
                    add(&dp[s1 | (1 << a1[i])][s2 | (1 << b1[i])], cur * inv2 % MOD);
                    add(&dp[s1 | (1 << a2[i])][s2 | (1 << b2[i])], cur * inv2 % MOD);
                }
            }
        }
    }

    ll ans = 0;
    for (int s = 0; s < (1 << n); s++) {
        add(&ans, dp[(1 << n) - 1][s]);
    }
    
    ans = ans * quick_pow(2, n) % MOD;
    printf("%lld\n", ans);

    return 0;
}