#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 10000

typedef long long ll;

int n, t;
int fail[MAXN];
char s[MAXN];

void get_fail(int m) {
    fail[0] = fail[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = fail[i];
        while (j && s[i] != s[j]) j = fail[j];
        fail[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &t);
    
    for (int i = 1; i <= t; i++) {
        int m;
        scanf("%d", &m);
        
        for (int j = 0; j < m; j++) {
            int x;
            scanf("%d", &x);
            s[j] = x;
        }
        
        get_fail(m);
        
        ll dp[MAXN] = {0};
        dp[0] = n;
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < n; k++) {
                dp[j] = (dp[j] + dp[j-1]) % MOD;
            }
            dp[j] = (dp[j] - dp[fail[j]] + MOD) % MOD;
        }
        
        ll inv_n = quick_pow(n, MOD - 2);
        ll res = dp[m] * inv_n % MOD;
        
        printf("%04lld\n", res);
    }
    
    return 0;
}