#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Function to compute (base^exp) % mod using fast exponentiation
uint64_t power_mod(uint64_t base, uint64_t exp, uint64_t mod){
    uint64_t result = 1;
    base %= mod;
    while(exp > 0){
        if(exp & 1){
            result = (__int128(result) * base) % mod;
        }
        base = (__int128(base) * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Function to compute gcd
uint64_t gcd(uint64_t a, uint64_t b){
    while(b){
        uint64_t tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Function to compute Euler's Totient function
uint64_t totient(uint64_t n){
    uint64_t result = n;
    for(uint64_t i=2;i*i<=n;i++){
        if(n%i == 0){
            while(n%i ==0){
                n /=i;
            }
            result -= result / i;
        }
    }
    if(n >1){
        result -= result / n;
    }
    return result;
}

// Function to get all divisors of n
int get_divisors(uint64_t n, uint64_t *divisors){
    int count =0;
    for(uint64_t i=1;i*i<=n;i++){
        if(n%i ==0){
            divisors[count++] = i;
            if(n/i !=i){
                divisors[count++] = n/i;
            }
        }
    }
    return count;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        uint64_t n, k, p;
        scanf("%llu %llu %llu", &n, &k, &p);
        // Total strings
        uint64_t total = power_mod(k, n, p);
        // Number of palindromic strings
        uint64_t half = (n +1)/2;
        uint64_t pal = power_mod(k, half, p);
        // Number of strings with at least one palindromic rotation
        uint64_t divisors[64];
        int cnt = get_divisors(n, divisors);
        uint64_t rot =0;
        for(int i=0;i<cnt;i++){
            uint64_t d = divisors[i];
            uint64_t phi = totient(d);
            uint64_t len = n/d;
            uint64_t exp = (len +1)/2;
            rot = (rot + (__int128(phi) * power_mod(k, exp, p))%p)%p;
        }
        // Number of unique strings with palindromic rotations
        // Burnside's lemma already gives the count
        // Total hated strings: pal + rot - pal_overlap
        // Since palindromic strings are included in rot when d=1
        // So pal is already included in rot
        uint64_t hated = rot;
        printf("%llu\n", hated);
    }
}