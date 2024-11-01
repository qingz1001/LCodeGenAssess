#include <stdio.h>

typedef long long ll;

const ll MOD = 1000000007;

// Function to compute (base^exp) % mod using binary exponentiation
ll pow_mod_func(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    // Compute inverse of m modulo MOD
    ll invm = pow_mod_func(m, MOD-2, MOD);
    
    ll sum = 0;
    for(ll l=1; l<=n; l++){
        // m^l mod MOD
        ll m_l = pow_mod_func(m, l, MOD);
        
        // invm^l mod MOD
        ll invm_l = pow_mod_func(invm, l, MOD);
        
        // (1 - invm_l) mod MOD
        ll one_minus_invm_l = (1 - invm_l + MOD) % MOD;
        
        // (1 - invm_l)^(n - l +1) mod MOD
        ll pow_term = pow_mod_func(one_minus_invm_l, n - l +1, MOD);
        
        // (1 - pow_term) mod MOD
        ll sub_term = (1 - pow_term + MOD) % MOD;
        
        // term = (m^l * sub_term) mod MOD
        ll term = (m_l * sub_term) % MOD;
        
        // Add to sum
        sum = (sum + term) % MOD;
    }
    
    printf("%lld\n", sum);
    return 0;
}