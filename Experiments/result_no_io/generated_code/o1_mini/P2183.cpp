#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

// Structure to hold prime factors
typedef struct {
    ll prime;
    int power;
} Factor;

// Extended GCD to find x and y such that a*x + b*y = gcd(a,b)
ll extended_gcd_func(ll a, ll b, ll *x, ll *y){
    if(b == 0){
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd_func(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

// Function to find modular inverse of a mod m
ll inverse_func(ll a, ll mod){
    ll x, y;
    ll g = extended_gcd_func(a, mod, &x, &y);
    if(g != 1){
        return -1;
    }
    else{
        ll res = x % mod;
        if(res < 0) res += mod;
        return res;
    }
}

// Function to factorize P into its prime factors
int factorize(ll P, Factor factors[]){
    int count = 0;
    for(ll p = 2; p*p <= P; p++){
        if(P % p == 0){
            int power = 0;
            while(P % p == 0){
                power++;
                P /= p;
            }
            factors[count].prime = p;
            factors[count].power = power;
            count++;
        }
    }
    if(P > 1){
        factors[count].prime = P;
        factors[count].power = 1;
        count++;
    }
    return count;
}

// Function to compute multinomial coefficient modulo p^k
ll compute_multinomial(ll n, ll w[], int m, ll p, int k){
    ll p_k = 1;
    for(int i=0; i<k; i++) p_k *= p;
    
    // Allocate memory for factorials and inverse factorials
    ll *f = (ll*)malloc(sizeof(ll)*p);
    ll *invf = (ll*)malloc(sizeof(ll)*p);
    if(!f || !invf){
        // Memory allocation failed
        free(f);
        free(invf);
        return 0;
    }
    
    // Compute factorial modulo p^k
    f[0] = 1;
    for(int i=1; i<p; i++) f[i] = (f[i-1] * i) % p_k;
    
    // Compute inverse factorial modulo p^k
    for(int i=0; i<p; i++){
        invf[i] = inverse_func(f[i], p_k);
        if(invf[i] == -1){
            // Inverse doesn't exist, which shouldn't happen
            free(f);
            free(invf);
            return 0;
        }
    }
    
    ll res = 1;
    ll tmp_w[m];
    for(int i=0; i<m; i++) tmp_w[i] = w[i];
    
    while(n > 0 || 0){
        int any = 0;
        for(int i=0; i<m; i++) if(tmp_w[i] > 0) { any =1; break;}
        if(n ==0 && !any) break;
        
        ll n_i = n % p;
        ll sum_w_i = 0;
        ll w_i_digit[m];
        for(int i=0; i<m; i++){
            w_i_digit[i] = tmp_w[i] % p;
            sum_w_i += w_i_digit[i];
        }
        if(sum_w_i > n_i){
            res = 0;
            break;
        }
        // Compute c = f[n_i] * invf[w1_i] * ... * invf[wm_i] * invf[n_i - sum_w_i] mod p_k
        ll c = f[n_i];
        for(int i=0; i<m; i++) c = (c * invf[w_i_digit[i]]) % p_k;
        c = (c * invf[n_i - sum_w_i]) % p_k;
        res = (res * c) % p_k;
        
        n /= p;
        for(int i=0; i<m; i++) tmp_w[i] /= p;
    }
    
    free(f);
    free(invf);
    return res;
}

// Function to perform Chinese Remainder Theorem
ll crt_func(ll residues[], ll moduli[], int count){
    ll x = 0;
    ll M = 1;
    for(int i=0; i<count; i++){
        ll a = residues[i];
        ll m_i = moduli[i];
        ll g, s, t;
        g = extended_gcd_func(M, m_i, &s, &t);
        if( (a - x) % g != 0 ){
            return -1;
        }
        ll lcm = (M / g) * m_i;
        ll inv = inverse_func(M / g, m_i / g);
        if(inv == -1){
            return -1;
        }
        ll delta = (a - x) / g;
        ll tmp = (delta * inv) % (m_i / g);
        if(tmp <0) tmp += (m_i / g);
        x = (x + tmp * M) % lcm;
        if(x <0) x += lcm;
        M = lcm;
    }
    return x;
}

int main(){
    ll P;
    scanf("%lld", &P);
    
    // Factorize P
    Factor factors[20];
    int factor_count = factorize(P, factors);
    
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll w[m];
    for(int i=0; i<m; i++) scanf("%lld", &w[i]);
    
    // Compute sum_w
    ll sum_w =0;
    for(int i=0; i<m; i++) sum_w +=w[i];
    if(sum_w > n){
        printf("Impossible\n");
        return 0;
    }
    
    // Prepare residues and moduli for CRT
    ll residues[factor_count];
    ll moduli[factor_count];
    for(int i=0; i<factor_count; i++){
        ll p = factors[i].prime;
        int k = factors[i].power;
        ll mk =1;
        for(int j=0; j<k; j++) mk *=p;
        moduli[i] = mk;
        residues[i] = compute_multinomial(n, w, m, p, k);
    }
    
    // Perform CRT
    ll answer = crt_func(residues, moduli, factor_count);
    
    // If answer is -1, it's impossible, but according to problem it's always possible if sum_w <=n
    // However, multinomial coefficient might be 0 modulo P
    if(answer == -1){
        printf("Impossible\n");
    }
    else{
        printf("%lld\n", answer);
    }
    
    return 0;
}