#include <stdio.h>

typedef long long ll;

#define MOD 100000000

typedef struct {
    ll f;
    ll g;
} FibPair;

FibPair fib_fast_doubling(ll n) {
    if (n == 0) {
        FibPair base = {0, 1};
        return base;
    }
    FibPair half = fib_fast_doubling(n / 2);
    ll c = (half.f * ((2 * half.g % MOD) - half.f + MOD)) % MOD;
    ll d = (half.f * half.f % MOD + half.g * half.g % MOD) % MOD;
    if (n % 2 == 0) {
        FibPair res = {c, d};
        return res;
    } else {
        FibPair res = {d, (c + d) % MOD};
        return res;
    }
}

ll gcd_func(ll a, ll b){
    while(b !=0){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll k = gcd_func(n, m);
    FibPair result = fib_fast_doubling(k);
    printf("%lld\n", result.f % MOD);
    return 0;
}