#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ll;

// Function to compute (base^exp) % mod using fast exponentiation
ll powmod_func(ll base, ll exp, ll mod){
    ll res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = (__int128(res) * base) % mod;
        }
        base = (__int128(base) * base) % mod;
        exp >>=1;
    }
    return res;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    // Sieve of Eratosthenes
    int size = n+1;
    char *is_prime = (char*)malloc(size);
    memset(is_prime, 1, size);
    is_prime[0] = is_prime[1] = 0;
    for(ll p=2; p*p <=n; p++){
        if(is_prime[p]){
            for(ll multiple = p*p; multiple <=n; multiple +=p){
                is_prime[multiple] = 0;
            }
        }
    }
    
    ll ans = 1;
    for(ll p=2; p<=n; p++){
        if(is_prime[p]){
            ll c_p = n / p;
            ll power = powmod_func(2, c_p +1, m);
            ll term = (power -1) % m;
            if(term <0) term +=m;
            ans = (__int128(ans) * term) % m;
        }
    }
    
    printf("%lld\n", ans);
    free(is_prime);
    return 0;
}