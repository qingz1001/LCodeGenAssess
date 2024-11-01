#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_A 10000001

typedef long long ll;

ll powmod(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    static int cnt[MAX_A];
    int T, a;
    ll n;
    
    scanf("%d", &T);
    while (T--) {
        scanf("%lld %d", &n, &a);
        
        memset(cnt, 0, sizeof(int) * (a + 1));
        for (int i = 1; i <= a; i++) {
            for (int j = i; j <= a; j++) {
                for (int k = j; k <= a; k++) {
                    if (gcd(gcd(i, j), k) == 1) {
                        if (i == j && j == k) cnt[1]++;
                        else if (i == j || j == k) cnt[2]++;
                        else cnt[3]++;
                    }
                }
            }
        }
        
        ll total = cnt[1] + cnt[2] + cnt[3];
        ll ans = 0;
        
        for (int i = 1; i <= 3; i++) {
            if (cnt[i] == 0) continue;
            ll tmp = powmod(cnt[i], n);
            tmp = (tmp * powmod(i, MOD - 2)) % MOD;
            ans = (ans + tmp) % MOD;
        }
        
        ans = (ans * powmod(total, MOD - 2)) % MOD;
        printf("%lld\n", ans);
    }
    
    return 0;
}