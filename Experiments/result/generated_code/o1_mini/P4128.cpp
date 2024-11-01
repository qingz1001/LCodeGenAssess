#include <stdio.h>
#include <stdlib.h>

// Function to compute gcd
int gcd_func(int a, int b){
    while(b){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Fast exponentiation
long long powmod_func(long long a, long long b, long long mod){
    long long res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = (__int128(res) * a) % mod;
        }
        a = (__int128(a) * a) % mod;
        b >>= 1;
    }
    return res;
}

// Generate all partitions using backtracking
typedef struct {
    int *parts;
    int size;
} Partition;

long long n, m, p;
long long result = 0;
long long factorial[54];
long long inv_factorial[54];
long long inv_n_fact;

// Function to compute factorial modulo p
void compute_factorial(){
    factorial[0] = 1;
    for(int i = 1; i <= n; i++){
        factorial[i] = (__int128(factorial[i-1]) * i) % p;
    }
}

// Function to compute inverse factorial modulo p
long long compute_inverse(long long a){
    return powmod_func(a, p-2, p);
}

// Recursive function to generate partitions
void generate_partitions(int remaining, int max, int *current, int size){
    if(remaining == 0){
        // Process current partition
        // Count multiplicities
        int ml[54] = {0};
        for(int i = 0; i < size; i++){
            ml[current[i]]++;
        }
        // Compute denominator = product of (ml! * l^ml) mod p
        long long denom = 1;
        for(int l = 1; l <= n; l++){
            if(ml[l] > 0){
                // Compute ml! mod p
                long long ml_fact = 1;
                for(int f = 1; f <= ml[l]; f++) {
                    ml_fact = (__int128(ml_fact) * f) % p;
                }
                // Compute l^ml mod p
                long long l_pow_ml = powmod_func(l, ml[l], p);
                // Multiply to denom
                denom = (__int128(denom) * ml_fact) % p;
                denom = (__int128(denom) * l_pow_ml) % p;
            }
        }
        // Compute |C_lambda| = n! * inv(denom) mod p
        long long C_lambda = (__int128(factorial[n]) * compute_inverse(denom)) % p;
        // Compute c_lambda
        // First, collect all cycle lengths
        int cycle_lengths[54];
        int idx = 0;
        for(int l =1; l <=n; l++) {
            for(int cnt =0; cnt < ml[l]; cnt++) {
                cycle_lengths[idx++] = l;
            }
        }
        // Number of cycles with length >=2
        int cycles_ge2 =0;
        for(int i =0; i < idx; i++) {
            if(cycle_lengths[i] >=2) cycles_ge2++;
        }
        // Sum of gcd over all unordered pairs
        long long sum_gcd =0;
        for(int i =0; i < idx; i++) {
            for(int j =i+1; j < idx; j++) {
                sum_gcd += gcd_func(cycle_lengths[i], cycle_lengths[j]);
            }
        }
        long long c_lambda = (__int128(cycles_ge2) + sum_gcd) % p;
        // Compute m^c_lambda mod p
        long long m_pow_c = powmod_func(m, c_lambda, p);
        // Compute term = C_lambda * m_pow_c mod p
        long long term = (__int128(C_lambda) * m_pow_c) % p;
        // Add to result
        result = (result + term) % p;
        return;
    }
    for(int i = (max < remaining ? max : remaining); i >=1; i--){
        current[size] = i;
        generate_partitions(remaining -i, i, current, size+1);
    }
}

int main(){
    scanf("%lld %lld %lld", &n, &m, &p);
    compute_factorial();
    // Generate all partitions
    int current[54];
    generate_partitions(n, n, current, 0);
    // Compute inv(n!) mod p
    long long n_fact = factorial[n];
    inv_n_fact = compute_inverse(n_fact);
    // Compute final answer
    long long answer = (__int128(result) * inv_n_fact) % p;
    printf("%lld\n", answer);
    return 0;
}