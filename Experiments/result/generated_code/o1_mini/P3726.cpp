#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function to compute x^y mod m
uint64_t powmod_func(uint64_t x, uint64_t y, uint64_t m){
    uint64_t res = 1;
    x %= m;
    while(y > 0){
        if(y & 1){
            res = (__int128(res) * x) % m;
        }
        x = (__int128(x) * x) % m;
        y >>=1;
    }
    return res;
}

// Extended Euclidean Algorithm to find inverse
long long extended_gcd_func(long long a, long long b, long long* x, long long* y){
    if(b ==0){
        *x =1;
        *y =0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd_func(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

// Function to find inverse of a mod m
uint64_t inverse_mod(uint64_t a, uint64_t m){
    long long x, y;
    long long g = extended_gcd_func(a, m, &x, &y);
    if(g !=1){
        return 0; // Inverse doesn't exist
    }
    else{
        long long res = x % m;
        if(res <0) res +=m;
        return res;
    }
}

// Function to compute v_p(n!)
int v_p(uint64_t n, int p){
    int cnt =0;
    while(n >= p){
        n /=p;
        cnt +=n;
    }
    return cnt;
}

// Function to compute C(n,d) mod p^e
uint64_t binom_mod_pe(uint64_t n, int d, int p, int e){
    if(d > n) return 0;
    if(d ==0 || d ==n) return 1;
    uint64_t pe =1;
    for(int i=0;i<e;i++) pe *=p;
    // Calculate v_p(n!) - v_p(d!) - v_p(n-d)!
    int vp =0;
    uint64_t nn =n;
    vp += v_p(nn, p);
    nn = d;
    vp -= v_p(nn, p);
    nn = n -d;
    vp -= v_p(nn, p);
    if(vp >=e){
        return 0;
    }
    // Now compute C(n,d) / p^vp mod p^(e)
    uint64_t res =1;
    int total_v = vp;
    for(int i=1;i<=d;i++){
        uint64_t num = n -i +1;
        uint64_t denom = i;
        int cnt_num =0, cnt_denom=0;
        while(num %p ==0){
            cnt_num++;
            num /=p;
        }
        while(denom %p ==0){
            cnt_denom++;
            denom /=p;
        }
        total_v += (cnt_num - cnt_denom);
        // Now denom is not divisible by p
        uint64_t inv = inverse_mod(denom, pe);
        res = (__int128(res) * (num % pe)) % pe;
        res = (__int128(res) * inv) % pe;
    }
    if(total_v >=e){
        return 0;
    }
    res = (__int128(res) * powmod_func(p, total_v, pe)) % pe;
    return res;
}

// Function to compute CCRT for two moduli
uint64_t crt(uint64_t a1, uint64_t m1, uint64_t a2, uint64_t m2){
    // Solve x ≡ a1 mod m1 and x ≡ a2 mod m2
    // m1 and m2 are powers of 2 and 5 respectively, hence coprime
    // x = a1 + m1 * ((a2 - a1) / m1 inverse mod m2)
    uint64_t inv = inverse_mod(m1, m2);
    if(inv ==0){
        return 0;
    }
    uint64_t x = a1 + m1 * ((__int128)(a2 - a1) * inv % m2);
    return x;
}

int main(){
    uint64_t a, b;
    int k;
    while(scanf("%llu %llu %d", &a, &b, &k) !=EOF){
        uint64_t n = a + b;
        // Compute sum C(n,d) for d=0 to a-1
        // Since C(n,d) = C(n, n-d), and a-1 <=1e4, we compute C(n,d) for d=0 to a-1
        // Each C(n,d) modulo 2^k and 5^k
        // Then combine via CRT to get C(n,d) mod10^k
        // Finally, sum them up modulo10^k
        // Precompute 2^k and 5^k
        uint64_t p1 =1;
        for(int i=0;i<k;i++) p1 *=2;
        uint64_t p2 =1;
        for(int i=0;i<k;i++) p2 *=5;
        uint64_t mod = p1 * p2;
        uint64_t sum =0;
        int max_d = a < (n+1) ? a-1 : n;
        if(a ==0){
            max_d =0;
        }
        for(int d=0; d <a && d <=n; d++){
            uint64_t c2 = binom_mod_pe(n, d, 2, k);
            uint64_t c5 = binom_mod_pe(n, d, 5, k);
            uint64_t c10 = crt(c2, p1, c5, p2);
            sum = (sum + c10) % mod;
        }
        // Now, print sum with leading zeros up to k digits
        char buffer[20];
        sprintf(buffer, "%llu", sum);
        int len = strlen(buffer);
        if(len <k){
            for(int i=0;i<k -len;i++) printf("0");
        }
        printf("%s\n", buffer);
    }
    return 0;
}