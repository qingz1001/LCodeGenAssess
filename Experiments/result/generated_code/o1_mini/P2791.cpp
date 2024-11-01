#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAX_L 200000

typedef long long ll;

// Fast exponentiation: computes a^b mod mod
ll pow_mod_func(ll a, ll b, ll mod_val){
    ll res = 1;
    a %= mod_val;
    while(b > 0){
        if(b & 1){
            res = res * a % mod_val;
        }
        a = a * a % mod_val;
        b >>= 1;
    }
    return res;
}

// Function to compute minimum of three integers
int min_three(int a, int b, int c){
    if(a < b){
        return (a < c) ? a : c;
    }
    else{
        return (b < c) ? b : c;
    }
}

int main(){
    int N, M, S;
    int L;
    scanf("%d %d %d %d", &N, &M, &S, &L);
    
    // Allocate memory for S_L
    // Using one array and updating it in place
    int *S_arr = (int*)calloc(L+1, sizeof(int));
    S_arr[0] = 1;
    for(int n=1; n<=L; n++){
        for(int j = n; j >=1; j--){
            S_arr[j] = (( ( (ll)j * S_arr[j]) % MOD ) + S_arr[j-1]) % MOD;
        }
    }
    
    // Process each query
    for(int q=0; q<S; q++){
        int n_i, m_i, k_i;
        scanf("%d %d %d", &n_i, &m_i, &k_i);
        
        int max_j = min_three(k_i, m_i, L);
        ll sum = 0;
        ll fact_m = 1;
        ll fact_k = 1;
        ll inv_n = 1;
        
        for(int j=1; j<=max_j; j++){
            // Compute fact_m = (m_i) * (m_i-1) * ... * (m_i -j +1) mod MOD
            fact_m = fact_m * ((ll)(m_i - j + 1)) % MOD;
            // Compute fact_k = (k_i) * (k_i-1) * ... * (k_i -j +1) mod MOD
            fact_k = fact_k * ((ll)(k_i - j + 1)) % MOD;
            // Compute inv_a = inv(n_i -j +1) mod MOD
            ll a = n_i - j + 1;
            ll inv_a = pow_mod_func(a, MOD-2, MOD);
            // Update inv_n = inv_n * inv_a mod MOD
            inv_n = inv_n * inv_a % MOD;
            // Compute term = S_L[j] * fact_m * fact_k * inv_n mod MOD
            ll term = (( ( (ll)S_arr[j] * fact_m) % MOD ) * fact_k) % MOD;
            term = (term * inv_n) % MOD;
            // Update sum
            sum = (sum + term) % MOD;
        }
        printf("%lld\n", sum);
    }
    
    // Free allocated memory
    free(S_arr);
    return 0;
}