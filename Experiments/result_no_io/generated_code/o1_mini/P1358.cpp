#include <stdio.h>

#define MOD 10007

typedef long long ll;

// Fast exponentiation to compute x^power mod MOD
ll power_mod(ll x, ll power) {
    ll result = 1;
    x = x % MOD;
    while (power > 0) {
        if (power & 1)
            result = (result * x) % MOD;
        x = (x * x) % MOD;
        power >>= 1;
    }
    return result;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[m];
    for(int i=0;i<m;i++) scanf("%d", &a[i]);
    
    // Compute n! % MOD
    int fact_n = 1;
    for(int i=2;i<=n;i++) {
        fact_n = (fact_n * i) % MOD;
    }
    
    // Compute product of a_i! % MOD
    int fact_a = 1;
    for(int i=0;i<m;i++) {
        for(int j=2; j<=a[i]; j++) {
            fact_a = (fact_a * j) % MOD;
        }
    }
    
    // Compute inverse of fact_a modulo MOD
    ll inv_fact_a = power_mod(fact_a, MOD-2);
    
    // Compute answer
    ll answer = (fact_n * inv_fact_a) % MOD;
    printf("%lld\n", answer);
    return 0;
}