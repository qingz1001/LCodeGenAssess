#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 998244353

typedef long long ll;

// Fast exponentiation
ll powmod_func(ll a, ll b, ll mod) {
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
    int n, m, l;
    scanf("%d %d %d", &n, &m, &l);
    
    // Read S
    int *S = (int*)malloc(l * sizeof(int));
    for(int i=0;i<l;i++) scanf("%d", &S[i]);
    
    // Compute prefix function
    int *pi = (int*)malloc(l * sizeof(int));
    pi[0] =0;
    for(int i=1;i<l;i++){
        int j = pi[i-1];
        while(j >0 && S[j] != S[i]){
            j = pi[j-1];
        }
        if(S[j] == S[i]){
            j++;
        }
        pi[i] = j;
    }
    
    // Initialize dp arrays
    // Use malloc to allocate large arrays
    unsigned int *dp_prev = (unsigned int*)calloc(l, sizeof(unsigned int));
    unsigned int *dp_new_arr = (unsigned int*)calloc(l, sizeof(unsigned int));
    unsigned int *sum = (unsigned int*)calloc(l, sizeof(unsigned int));
    dp_prev[0] =1;
    
    for(int step=1; step<=n; step++){
        // Reset sum
        for(int j=0; j<l; j++) sum[j] =0;
        
        // Compute sum[j] = sum of dp_prev[k] where f[k] = j
        for(int k=0; k<l; k++){
            int fk = pi[k];
            sum[fk] += dp_prev[k];
            if(sum[fk] >= MOD) sum[fk] -= MOD;
        }
        
        // Compute dp_new[j] = (j >0 ? dp_prev[j-1] : 0) + (m-1)*sum[j]
        for(int j=0; j<l; j++){
            unsigned long long mult = ((unsigned long long)(m -1) * (unsigned long long)sum[j]) % MOD;
            unsigned long long temp = (j >0 ? (unsigned long long)dp_prev[j-1] : 0) + mult;
            if(temp >= MOD) temp -= MOD;
            dp_new_arr[j] = temp;
        }
        
        // Swap dp_prev and dp_new
        unsigned int *temp_ptr = dp_prev;
        dp_prev = dp_new_arr;
        dp_new_arr = temp_ptr;
    }
    
    // Compute dp_n = sum(dp_prev[j] for j=0 to l-1)
    unsigned long long dp_n =0;
    for(int j=0; j<l; j++) dp_n = (dp_n + dp_prev[j]) % MOD;
    
    // Compute total = m^n mod MOD
    ll total = powmod_func((ll)m, (ll)n, MOD);
    
    // Compute inv_total = m^(n*(MOD-2)) mod MOD
    ll exponent = ((ll)n * (MOD - 2));
    ll inv_total = powmod_func((ll)m, exponent, MOD);
    
    // Compute (total - dp_n) * inv_total mod MOD
    ll diff = (total >= dp_n) ? (total - dp_n) : (total + MOD - dp_n);
    ll ans = (diff * inv_total) % MOD;
    
    printf("%lld\n", ans);
    
    // Free allocated memory
    free(S);
    free(pi);
    free(dp_prev);
    free(dp_new_arr);
    free(sum);
    
    return 0;
}