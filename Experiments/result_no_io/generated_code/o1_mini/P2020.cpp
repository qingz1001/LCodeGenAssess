#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef long long ll;

// Structure to hold Fibonacci pair
typedef struct {
    ll a;
    ll b;
} FibPair;

// Fast doubling to compute Fib(n) mod m
FibPair fib_fast_doubling(ll n, ll mod) {
    if (n == 0)
        return (FibPair){0, 1};
    FibPair p = fib_fast_doubling(n >> 1, mod);
    ll c = (p.a * ((2 * p.b % mod + mod - p.a) % mod)) % mod;
    ll d = (p.a * p.a % mod + p.b * p.b % mod) % mod;
    if (n & 1)
        return (FibPair){d, (c + d) % mod};
    else
        return (FibPair){c, d};
}

int main(){
    ll n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);
    
    // Compute Pisano period for modulo k
    ll a = 1, b = 1;
    ll period = 0;
    ll count_per_period = 0;
    ll *fib_mod_k = malloc(sizeof(ll)*6000000);
    if(!fib_mod_k){
        return 0;
    }
    while(1){
        ll c = (a + b) % k;
        if(c ==1){
            count_per_period++;
        }
        fib_mod_k[period++] = c;
        a = b;
        b = c;
        if(a ==1 && b ==1){
            if(c ==1){
                count_per_period--;
            }
            period--;
            break;
        }
        if(period >= 6000000){
            break;
        }
    }
    
    // Compute C(n)
    ll C =0;
    if(n >=3){
        ll full_periods = (n -2) / period;
        ll remaining = (n -2) % period;
        C = full_periods * count_per_period;
        for(ll i=0;i<remaining;i++){
            if(fib_mod_k[i]==1){
                C++;
            }
        }
    }
    free(fib_mod_k);
    
    // Compute Fib(n) mod p
    FibPair fib = fib_fast_doubling(n, p);
    ll fib_n_mod_p = fib.a;
    
    // Compute answer
    ll answer;
    if(n ==1 || n==2){
        answer = 1 % p;
    }
    else{
        answer = (fib_n_mod_p - (C % p) + p) % p;
    }
    printf("%lld", answer);
    return 0;
}