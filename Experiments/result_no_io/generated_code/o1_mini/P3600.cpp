#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

const ll MOD = 666623333;

// Fast exponentiation
ll powmod_func(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

int main(){
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);
    int *k = (int*)malloc(q * sizeof(int));
    for(int i=0; i<q; i++){
        int l, r;
        scanf("%d %d", &l, &r);
        k[i] = r - l +1;
    }
    // Compute sum_k
    ll sum_k =0;
    for(int i=0; i<q; i++) sum_k += k[i];
    // Precompute pow_x[k]
    ll *pow_x = (ll*)malloc((2001) * sizeof(ll));
    pow_x[0] =1;
    for(int i=1; i<=2000; i++) pow_x[i] = pow_x[i-1] * x % MOD;
    // Compute b = x^sum_k mod MOD
    ll b = powmod_func(x, sum_k, MOD);
    // Compute a
    ll a =0;
    // Precompute pow_x_sum_k = b
    for(int v=1; v<=x; v++){
        int s = x - v +1;
        // Compute s^k for k up to 2000
        ll s_pows_temp =1;
        // To store s^k_i for each query
        // Since k_i <=2000 and q <=2000, use a temporary array
        // To save time, compute s^k_i on the fly
        // Compute product
        ll product =1;
        // Precompute s^k_i
        // Compute s_pows_temp up to max k_i
        // To speed up, compute all needed s^k_i first
        // Create an array for s^k_i
        // But to save memory, compute on the fly
        // Initialize s_pows[k_i] as 1
        // Create a temporary array
        // Or compute s^k_i iteratively
        // Here, compute s^{k_i} for each query
        // and multiply (pow_x[k_i] - s^{k_i}) to product
        // Precompute s_pows_temp
        // To optimize, precompute s^k up to 2000
        // and access k_i
        // Implement simple power computation per query
        // Since q and x are small, it's feasible
        // Alternatively, precompute s^k up to 2000
        // Create an array for s^k
        ll *s_pows = (ll*)malloc((2001) * sizeof(ll));
        s_pows[0] =1;
        for(int ki=1; ki<=2000; ki++) s_pows[ki] = s_pows[ki-1] * s % MOD;
        for(int i=0; i<q; i++){
            int ki = k[i];
            ll term = (pow_x[ki] - s_pows[ki] + MOD) % MOD;
            product = product * term % MOD;
            if(product ==0) break;
        }
        free(s_pows);
        // Update a
        a = (a + b) % MOD;
        a = (a - product + MOD) % MOD;
    }
    free(pow_x);
    free(k);
    // Compute inverse of b
    ll inv_b = powmod_func(b, MOD-2, MOD);
    // Compute E = a * inv_b % MOD
    ll E = a * inv_b % MOD;
    printf("%lld\n", E);
    return 0;
}