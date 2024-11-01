#include <stdio.h>
#include <string.h>

#define MOD 998244353

typedef long long ll;

ll n;
char s[100005];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%s", s);
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        n = (n * 10 + s[i] - '0') % (MOD - 1);
    }
    
    ll ans1 = 1, ans2 = 1;
    
    // kkksc03
    ans1 = ans1 * ((n / 6 + 1) % MOD) % MOD;
    ans1 = ans1 * ((n < 9 ? n + 1 : 10) % MOD) % MOD;
    ans1 = ans1 * ((n < 5 ? n + 1 : 6) % MOD) % MOD;
    ans1 = ans1 * ((n / 4 + 1) % MOD) % MOD;
    ans1 = ans1 * ((n < 7 ? n + 1 : 8) % MOD) % MOD;
    
    // lzn
    ans2 = ans2 * ((n / 2 + 1) % MOD) % MOD;
    ans2 = ans2 * ((n < 1 ? n + 1 : 2) % MOD) % MOD;
    ans2 = ans2 * ((n / 8 + 1) % MOD) % MOD;
    ans2 = ans2 * ((n / 10 + 1) % MOD) % MOD;
    ans2 = ans2 * ((n < 3 ? n + 1 : 4) % MOD) % MOD;
    
    ll ans = (ans1 + ans2 - 1 + MOD) % MOD;
    printf("%lld\n", ans);
    
    return 0;
}