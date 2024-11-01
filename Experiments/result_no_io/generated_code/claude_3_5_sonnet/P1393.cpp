#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 200005

typedef long long ll;

ll quick_pow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

ll inv(ll x) {
    return quick_pow(x, MOD - 2);
}

int n, m, len;
int s[MAXN];
ll dp[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &len);
    for (int i = 0; i < len; i++) {
        scanf("%d", &s[i]);
    }

    ll inv_m = inv(m);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1] * m % MOD;
        if (i >= len) {
            int match = 1;
            for (int j = 0; j < len; j++) {
                if (s[j] > m) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                ll subtract = dp[i-len];
                for (int j = 0; j < len; j++) {
                    subtract = subtract * inv_m % MOD;
                }
                dp[i] = (dp[i] - subtract + MOD) % MOD;
            }
        }
    }

    ll total = quick_pow(m, n);
    ll result = (total - dp[n] + MOD) % MOD;
    printf("%lld\n", result);

    return 0;
}