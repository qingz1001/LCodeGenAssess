#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MOD 998244353
#define root 15311432  // primitive root for 998244353
#define root_inv 469870224
#define root_pw 1<<23

typedef long long ll;

// Fast exponentiation
ll power_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

// Inverse modulo
ll inv(ll a){
    return power_pow(a, MOD-2);
}

// NTT implementation
void ntt(ll a[], int n, int invert){
    for(int i=1,j=0;i<n;i++){
        int bit = n>>1;
        while(j>=bit){
            j -= bit;
            bit >>=1;
        }
        if(j < bit) j += bit;
        if(i < j){
            ll tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    for(int len=2; len<=n; len <<=1){
        ll wlen = invert ? power_pow(root_inv, root_pw / len) : power_pow(root, root_pw / len);
        for(int i=0;i<n;i+=len){
            ll w =1;
            for(int j=0;j<len/2;j++){
                ll u = a[i+j];
                ll v = a[i+j+len/2] * w % MOD;
                a[i+j] = (u + v) % MOD;
                a[i+j+len/2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if(invert){
        ll n_inv = inv(n);
        for(int i=0;i<n;i++) a[i] = a[i] * n_inv % MOD;
    }
}

// Multiply two polynomials
ll* multiply(ll a[], int n, ll b[], int m){
    int size=1;
    while(size < n + m) size <<=1;
    ll* fa = (ll*)calloc(size, sizeof(ll));
    ll* fb = (ll*)calloc(size, sizeof(ll));
    for(int i=0;i<n;i++) fa[i] = a[i];
    for(int i=0;i<m;i++) fb[i] = b[i];
    ntt(fa, size, 0);
    ntt(fb, size, 0);
    for(int i=0;i<size;i++) fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, size, 1);
    return fa;
}

int main(){
    int n;
    scanf("%d", &n);
    
    // Precompute factorial and inv_fact
    ll *fact = (ll*)malloc((n+2)*sizeof(ll));
    ll *inv_fact_arr = (ll*)malloc((n+2)*sizeof(ll));
    fact[0]=1;
    for(int i=1;i<=n+1;i++) fact[i] = fact[i-1]*i % MOD;
    inv_fact_arr[n+1] = inv(fact[n+1]);
    for(int i=n;i>=0;i--) inv_fact_arr[i] = inv_fact_arr[i+1]*(i+1)%MOD;
    
    // Compute e^t up to n
    ll *et = (ll*)calloc(n+1, sizeof(ll));
    et[0] = 1;
    for(int i=1;i<=n;i++) et[i] = et[i-1] + inv_fact_arr[i];
    for(int i=0;i<=n;i++) et[i] %= MOD;
    
    // Compute 3 -2 e^t
    ll *three_minus_2et = (ll*)calloc(n+1, sizeof(ll));
    three_minus_2et[0] = (3 - 2*et[0]%MOD + MOD)%MOD;
    for(int i=1;i<=n;i++) {
        three_minus_2et[i] = (0 - 2*et[i]%MOD + MOD)%MOD;
    }
    
    // Prepare for inverse series
    // Initialize G with g0 = inv(three_minus_2et[0}) = inv(1)
    ll *G = (ll*)calloc(n+1, sizeof(ll));
    G[0] = inv(three_minus_2et[0]);
    // Iteratively compute G
    for(int i=1;i<=n;i++){
        ll val = 0;
        for(int j=1;j<=i;j++) {
            val = (val + 2 * et[j] * G[i-j]) % MOD;
        }
        G[i] = (0 - val) * inv(3) % MOD;
        if(G[i]<0) G[i]+=MOD;
    }
    
    // Compute g(n) = G[n]
    // Compute f(n) = sum_{i=0}^n g(i)
    ll f =0;
    for(int i=0;i<=n;i++) {
        f = (f + G[i]) % MOD;
    }
    printf("%lld\n", f);
    
    // Free memory
    free(fact);
    free(inv_fact_arr);
    free(et);
    free(three_minus_2et);
    free(G);
    return 0;
}