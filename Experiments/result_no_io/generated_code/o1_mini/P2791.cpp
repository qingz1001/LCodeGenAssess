#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 998244353

typedef long long ll;

// Fast exponentiation
ll power_ll(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main(){
    ll N, M, S, L;
    scanf("%lld %lld %lld %lld", &N, &M, &S, &L);
    
    // Allocate memory for factorial and inv_fact
    ll *fact = (ll*)malloc((N+1) * sizeof(ll));
    if(!fact){
        return 1;
    }
    fact[0] = 1;
    for(ll i=1;i<=N;i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    
    // Compute inv_fact
    ll *inv_fact = (ll*)malloc((N+1) * sizeof(ll));
    if(!inv_fact){
        free(fact);
        return 1;
    }
    inv_fact[N] = power_ll(fact[N], MOD-2);
    for(ll i=N-1;i>=0;i--){
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
    
    for(ll s=0; s<S; s++){
        ll ni, mi, ki;
        scanf("%lld %lld %lld", &ni, &mi, &ki);
        // Calculate C(ni, ki)
        if(ki > ni || mi > ni || ki < 0 || mi < 0){
            printf("0\n");
            continue;
        }
        ll C_nk = fact[ni] * inv_fact[ki] % MOD * inv_fact[ni - ki] % MOD;
        if(C_nk == 0){
            printf("0\n");
            continue;
        }
        // Determine x range
        ll x_min = ki > (ni - mi) ? ki - (ni - mi) : 0;
        ll x_max = mi < ki ? mi : ki;
        ll numerator = 0;
        for(ll x = x_min; x <= x_max; x++){
            // Compute C(mi, x)
            if(x > mi){
                continue;
            }
            ll C_mx = fact[mi] * inv_fact[x] % MOD * inv_fact[mi - x] % MOD;
            // Compute C(ni - mi, ki - x)
            ll ky = ki - x;
            if(ky > (ni - mi) || ky < 0){
                continue;
            }
            ll C_nmky = fact[ni - mi] * inv_fact[ky] % MOD * inv_fact[ni - mi - ky] % MOD;
            // Compute x^L
            ll xL = power_ll(x, L);
            // Add to numerator
            numerator = (numerator + xL * C_mx % MOD * C_nmky % MOD) % MOD;
        }
        // Compute E(x^L) = numerator * inv(C_nk) mod MOD
        ll inv_Cnk = power_ll(C_nk, MOD-2);
        ll E = numerator * inv_Cnk % MOD;
        printf("%lld\n", E);
    }
    
    free(fact);
    free(inv_fact);
    return 0;
}