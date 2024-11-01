#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_A 10000000
#define MOD 1000000007
#define SIX_MOD MOD*6

typedef long long ll;

// Fast exponentiation
ll power_mod(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    if(a <0) a += mod;
    while(b >0){
        if(b &1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

int main(){
    // Allocate memory
    unsigned char *is_prime = (unsigned char*)malloc((MAX_A +1) * sizeof(unsigned char));
    memset(is_prime, 1, MAX_A +1);
    is_prime[0] = is_prime[1] = 0;
    
    // Initialize mu and phi
    ll *mu = (ll*)malloc((MAX_A +1) * sizeof(ll));
    ll *phi = (ll*)malloc((MAX_A +1) * sizeof(ll));
    for(int i=0;i<=MAX_A;i++){
        mu[i]=1;
        phi[i]=i;
    }
    
    // Sieve of Eratosthenes to compute mu and phi
    for(int p=2;p<=MAX_A;p++){
        if(is_prime[p]){
            for(int multiple=p; multiple<=MAX_A; multiple+=p){
                is_prime[multiple]=0;
                phi[multiple] -= phi[multiple]/p;
            }
            // Handle mu
            for(ll multiple = p; multiple <= MAX_A; multiple +=p){
                mu[multiple] *= -1;
            }
            ll p_sq = (ll)p * p;
            for(ll multiple = p_sq; multiple <= MAX_A; multiple += p_sq){
                mu[multiple] =0;
            }
        }
    }
    
    // Precompute prefix sum of phi
    ll *prefix_phi = (ll*)malloc((MAX_A +1) * sizeof(ll));
    prefix_phi[0]=0;
    for(int i=1;i<=MAX_A;i++) prefix_phi[i]=prefix_phi[i-1] + phi[i];
    
    // Read number of test cases
    int T;
    scanf("%d", &T);
    while(T--){
        ll n, a;
        scanf("%lld %lld", &n, &a);
        if(a > MAX_A) a = MAX_A;
        // Compute sum_mu
        ll sum_mu =0;
        for(ll d=1; d<=a; d++){
            if(mu[d]==0) continue;
            ll c = a / d;
            ll c_mod = c % (MOD *6);
            ll c3 = (c_mod * c_mod) % (MOD *6);
            c3 = (c3 * c_mod) % (MOD *6);
            ll term;
            if(mu[d]==1){
                term = c3;
            }
            else{
                term = (MOD *6 - c3) % (MOD *6);
            }
            sum_mu = (sum_mu + term) % (MOD *6);
        }
        // Compute sum_phi
        ll sum_phi = prefix_phi[a];
        // Count_xyz is always 1
        // Compute m = (sum_mu +3*sum_phi +2 ) /6
        ll total = sum_mu + 3 * sum_phi +2;
        ll m = total /6;
        // Compute m mod MOD
        ll m_mod = m % MOD;
        // Compute x = (m-1) mod MOD
        ll x = (m_mod >=1) ? (m_mod -1) : (MOD -1);
        // Compute pow(x, n) mod MOD
        ll pow_x_n = power_mod(x, n, MOD);
        // Compute term2
        ll term2;
        if(n %2 ==0){
            term2 =x;
        }
        else{
            term2 = (MOD -x) % MOD;
        }
        // Compute sum = (pow_x_n + term2) % MOD
        ll sum = (pow_x_n + term2) % MOD;
        // Compute inv_n = n^{-1} mod MOD
        ll n_mod = n % MOD;
        if(n_mod ==0){
            // Undefined, set answer to0
            printf("0\n");
            continue;
        }
        ll inv_n = power_mod(n_mod, MOD-2, MOD);
        // Compute answer = sum * inv_n % MOD
        ll answer = (sum * inv_n) % MOD;
        printf("%lld\n", answer);
    }
    
    // Free memory
    free(is_prime);
    free(mu);
    free(phi);
    free(prefix_phi);
    return 0;
}