#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

ll power(ll base, ll exp) {
    if (exp == 0) return 1;
    ll half = power(base, exp / 2);
    if (exp % 2 == 0) return half * half % MOD;
    else return base * half * half % MOD;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n, a;
        scanf("%lld %lld", &n, &a);

        if (a == 1) {
            printf("0\n");
            continue;
        }

        ll count = 0;
        for (ll i = 1; i <= a; i++) {
            for (ll j = 1; j <= a; j++) {
                for (ll k = 1; k <= a; k++) {
                    if (gcd(i, gcd(j, k)) == 1 && (i != j || j != k || k != i)) {
                        count++;
                    }
                }
            }
        }

        ll result = 0;
        for (ll i = 0; i < n; i++) {
            result = (result * count) % MOD;
        }

        printf("%lld\n", result);
    }
    return 0;
}