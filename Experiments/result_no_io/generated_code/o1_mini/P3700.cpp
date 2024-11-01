#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXN 4000005
#define MOD 1000000007

typedef long long ll;

// Fast input
char buffer[1 << 25];
size_t buf_pos = 0, buf_len = 0;

inline char get_char() {
    if (buf_pos >= buf_len) {
        buf_len = fread(buffer, 1, sizeof(buffer), stdin);
        if (buf_len == 0) return EOF;
        buf_pos = 0;
    }
    return buffer[buf_pos++];
}

inline void read_int(ll *x) {
    *x = 0;
    char c = get_char();
    while(c < '0' || c > '9') {
        if(c == EOF) return;
        c = get_char();
    }
    while(c >= '0' && c <= '9') {
        *x = (*x)*10 + (c - '0');
        c = get_char();
    }
}

inline void read_signed_int(ll *x) {
    *x = 0;
    char c = get_char();
    int sign = 1;
    while((c < '0' || c > '9') && c != '-' && c != EOF) {
        c = get_char();
    }
    if(c == '-') {
        sign = -1;
        c = get_char();
    }
    while(c >= '0' && c <= '9') {
        *x = (*x)*10 + (c - '0');
        c = get_char();
    }
    *x *= sign;
}

int main(){
    ll m, n;
    read_int(&m);
    read_int(&n);
    
    // Initialize Möbius function
    ll *mu = (ll*)malloc((n+1) * sizeof(ll));
    for(ll i=0;i<=n;i++) mu[i] = 1;
    char *is_prime = (char*)malloc((n+1) * sizeof(char));
    memset(is_prime, 1, n+1);
    is_prime[0] = is_prime[1] = 0;
    for(ll p=2; p<=n; p++){
        if(is_prime[p]){
            for(ll multiple=p; multiple<=n; multiple += p){
                is_prime[multiple] = 0;
                mu[multiple] *= -1;
            }
            ll p_sq = p * p;
            for(ll multiple=p_sq; multiple<=n; multiple += p_sq){
                mu[multiple] = 0;
            }
        }
    }
    free(is_prime);
    
    // Precompute C[c] = sum_{d|c} mu[d] * ((floor(c/d)*(floor(c/d)+1)/2)^2)
    ll *C = (ll*)calloc(n+1, sizeof(ll));
    for(ll d=1; d<=n; d++){
        if(mu[d] == 0) continue;
        for(ll c=d; c<=n; c += d){
            ll q = c / d;
            ll t;
            if(q % 2 == 0){
                ll half = q / 2;
                t = (half % MOD) * ((q + 1) % MOD) % MOD;
            }
            else{
                ll half = (q + 1) / 2;
                t = (q % MOD) * (half % MOD) % MOD;
            }
            ll z = (t * t) % MOD;
            if(mu[d] == 1){
                C[c] = (C[c] + z) % MOD;
            }
            else { // mu[d] == -1
                C[c] = (C[c] - z) % MOD;
                if(C[c] < 0) C[c] += MOD;
            }
        }
    }
    
    // Initialize h_mod and modified_d_list
    ll *h_mod = (ll*)calloc(n+1, sizeof(ll)); // h_mod[d] = h(d) - 1
    ll *modified_ds = (ll*)malloc((m+1) * sizeof(ll));
    ll ds_count = 0;
    
    // Function to compute gcd
    #ifdef _MSC_VER
    #include <intrin.h>
    #pragma intrinsic(__gcd)
    #endif
    ll gcd(ll a, ll b){
        while(b){
            ll temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
    
    // Process each operation
    for(ll op=0; op<m; op++){
        ll a, b, x, k;
        read_int(&a);
        read_int(&b);
        read_int(&x);
        read_int(&k);
        ll d = gcd(a, b);
        ll h_new = x / (a * b);
        ll delta = h_new - 1;
        if(h_mod[d] == 0 && h_new !=1){
            h_mod[d] = delta;
            modified_ds[ds_count++] = d;
        }
        else if(h_mod[d] !=0 && h_new !=1){
            h_mod[d] = delta;
        }
        else if(h_mod[d] !=0 && h_new ==1){
            h_mod[d] = 0;
            // No removal from modified_ds to keep it simple
        }
        // Compute S = (k*(k+1)/2) % MOD
        ll S;
        if(k % 2 ==0){
            ll half = k /2;
            S = (half % MOD) * ((k +1) % MOD) % MOD;
        }
        else{
            ll half = (k +1) /2;
            S = (k % MOD) * (half % MOD) % MOD;
        }
        // Compute sum = (S * S) % MOD
        ll sum = (S * S) % MOD;
        // Iterate over modified_ds
        for(ll i=0; i<ds_count; i++){
            ll current_d = modified_ds[i];
            if(current_d > k) continue;
            if(h_mod[current_d] == 0) continue;
            ll c = k / current_d;
            if(c ==0) continue;
            ll temp = (h_mod[current_d] % MOD) * (current_d % MOD) % MOD;
            temp = (temp * (current_d % MOD)) % MOD;
            temp = (temp * (C[c] % MOD)) % MOD;
            sum = (sum + temp) % MOD;
        }
        printf("%lld\n", sum);
    }
    
    // Free memory
    free(mu);
    free(C);
    free(h_mod);
    free(modified_ds);
    
    return 0;
}