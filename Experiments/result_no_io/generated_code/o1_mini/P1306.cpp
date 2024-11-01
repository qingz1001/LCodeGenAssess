#include <stdio.h>

typedef long long ll;

#define MOD 100000000

ll gcd_ll(ll a, ll b){
    while(b){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void fib_fast_doubling(ll n, ll *fn){
    ll a = 0, b = 1, c, d;
    ll m = n;
    int i;
    for(i = 63; i >=0; i--){
        if((m >> i) & 1){
            // Compute c and d
            c = (a * ((2 * b % MOD + MOD - a) % MOD)) % MOD;
            d = (a * a % MOD + b * b % MOD) % MOD;
            a = d;
            b = (c + d) % MOD;
        }
        else{
            // Compute c and d
            c = (a * ((2 * b % MOD + MOD - a) % MOD)) % MOD;
            d = (a * a % MOD + b * b % MOD) % MOD;
            a = c;
            b = d;
        }
    }
    *fn = a;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll k = gcd_ll(n, m);
    ll result;
    fib_fast_doubling(k, &result);
    printf("%lld\n", result);
    return 0;
}