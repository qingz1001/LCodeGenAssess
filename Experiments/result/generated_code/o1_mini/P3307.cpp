#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define MAX_A 10000000
#define MOD 1000000007

typedef long long ll;

// Sieve of Eratosthenes to compute Möbius function and primes up to MAX_A
ll mu_arr[MAX_A + 1];
int is_prime[MAX_A + 1];
int primes[664579]; // Number of primes up to 1e7 is 664,579
int prime_count = 0;

// Function to compute Möbius function and store primes
void sieve_mu() {
    for(int i=0;i<=MAX_A;i++) {
        mu_arr[i] = 1;
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    for(int i=2;i<=MAX_A;i++) {
        if(is_prime[i]) {
            primes[prime_count++] = i;
            for(int j=i; j<=MAX_A; j+=i) {
                is_prime[j] = 0;
                mu_arr[j] *= -1;
            }
            ll sq = (ll)i * i;
            for(int j= (int)sq; j<=MAX_A; j+=sq) {
                mu_arr[j] = 0;
            }
        }
    }
}

// Fast exponentiation
ll power_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1){
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

// Function to factorize n using the list of primes
int factors[20];
int exponents[20];
int factor_count;

void factorize(ll n) {
    factor_count =0;
    for(int i=0;i<prime_count && (ll)primes[i]*primes[i] <=n;i++) {
        if(n % primes[i] ==0){
            factors[factor_count] = primes[i];
            exponents[factor_count] =0;
            while(n % primes[i] ==0){
                exponents[factor_count]++;
                n /= primes[i];
            }
            factor_count++;
        }
    }
    if(n >1){
        factors[factor_count] = n;
        exponents[factor_count] =1;
        factor_count++;
    }
}

// Function to generate all divisors
ll divisors[100000];
int total_divisors;

void generate_divisors(int idx, ll current) {
    if(idx == factor_count){
        divisors[total_divisors++] = current;
        return;
    }
    for(int i=0;i<=exponents[idx];i++){
        generate_divisors(idx +1, current);
        current *= factors[idx];
    }
}

int main(){
    sieve_mu();
    int T;
    scanf("%d", &T);
    while(T--){
        ll n, a;
        scanf("%lld %lld", &n, &a);
        // Compute m
        ll sum2 =0;
        ll sum3 =0;
        for(ll d=1; d<=a; d++){
            if(mu_arr[d] ==0) continue;
            ll cnt = a / d;
            if(cnt >=2){
                sum2 += mu_arr[d] * (cnt * (cnt -1) /2);
            }
            if(cnt >=3){
                sum3 += mu_arr[d] * (cnt * (cnt -1) * (cnt -2) /6);
            }
        }
        ll m = (1 + 2 * sum2 + sum3) % MOD;
        if(m <0) m += MOD;
        // Factorize n
        factorize(n);
        // Generate all divisors
        total_divisors =0;
        generate_divisors(0, 1);
        // Compute total sum
        ll total =0;
        for(int i=0;i<total_divisors;i++){
            ll d = divisors[i];
            // Compute phi(d)
            ll phi = d;
            for(int j=0; j<factor_count; j++){
                if(d % factors[j] ==0){
                    phi -= phi / factors[j];
                }
            }
            // Compute k =n/d
            ll k = n / d;
            // Compute (m-1)^k mod MOD
            ll term1 = power_pow((m -1 + MOD) % MOD, k);
            // Compute (-1)^k * (m-1)
            ll term2 = ((k %2)==0) ? ((m -1 + MOD) % MOD) : ((MOD - (m -1)) % MOD);
            // c(k) = (term1 + term2) mod MOD
            ll c = (term1 + term2) % MOD;
            // total += phi * c
            total = (total + (phi % MOD) * c % MOD ) % MOD;
        }
        // Compute inv(n mod MOD)
        ll n_mod = n % MOD;
        // Compute inverse using Fermat's little theorem
        ll inv_n = power_pow(n_mod, MOD -2);
        // Compute answer
        ll answer = (total * inv_n) % MOD;
        printf("%lld\n", answer);
    }
    return 0;
}