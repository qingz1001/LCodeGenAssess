#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

// Function to compute gcd using Euclidean algorithm
ull gcd_func(ull a, ull b){
    while(b){
        ull temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Sieve of Eratosthenes to generate primes up to 46340
int sieve_limit = 46340;
int prime_count = 0;
ull primes[5000];

void sieve(){
    int size = sieve_limit + 1;
    char *is_prime = (char*)malloc(size);
    for(int i=0;i<size;i++) is_prime[i] = 1;
    is_prime[0] = is_prime[1] = 0;
    for(int i=2;i*i <= sieve_limit;i++){
        if(is_prime[i]){
            for(int j=i*i; j<=sieve_limit; j+=i){
                is_prime[j] = 0;
            }
        }
    }
    for(int i=2;i<=sieve_limit;i++) {
        if(is_prime[i]){
            primes[prime_count++] = i;
        }
    }
    free(is_prime);
}

// Function to factorize n and store the exponents
int factorize(ull n, ull factors[], int *exponents){
    int idx = 0;
    for(int i=0;i<prime_count && primes[i]*primes[i] <= n;i++){
        if(n % primes[i] == 0){
            factors[idx] = primes[i];
            exponents[idx] = 0;
            while(n % primes[i] == 0){
                exponents[idx]++;
                n /= primes[i];
            }
            idx++;
        }
    }
    if(n > 1){
        factors[idx] = n;
        exponents[idx] = 1;
        idx++;
    }
    return idx;
}

// Recursive function to enumerate all divisors and count valid X
void enumerate(int idx, int total_factors, ull current, ull A, ull a1, ull b0, ull b1, ull *count, ull factors[], int exponents[]){
    if(idx == total_factors){
        // Check gcd(X, A) ==1
        if(gcd_func(current, A) != 1){
            return;
        }
        // Compute lcm(a1 * X, b0)
        ull a1X = a1 * current;
        ull g = gcd_func(a1X, b0);
        // To prevent overflow, use division first
        ull lcm = (a1X / g) * b0;
        if(lcm == b1){
            (*count)++;
        }
        return;
    }
    for(int i=0;i<=exponents[idx];i++){
        ull next = current;
        for(int j=0;j<i;j++) next *= factors[idx];
        enumerate(idx+1, total_factors, next, A, a1, b0, b1, count, factors, exponents);
    }
}

int main(){
    sieve();
    int n;
    if(scanf("%d", &n)!=1) return 0;
    while(n--){
        ull a0, a1, b0, b1;
        if(scanf("%llu %llu %llu %llu", &a0, &a1, &b0, &b1)!=4){
            printf("0\n");
            continue;
        }
        // Check a0 divisible by a1 and b1 divisible by b0
        if(a0 % a1 !=0 || b1 % b0 !=0){
            printf("0\n");
            continue;
        }
        ull A = a0 / a1;
        ull D = b1 / a1;
        // Factorize D
        ull factors[32];
        int exponents[32];
        int total_factors = factorize(D, factors, exponents);
        ull count = 0;
        enumerate(0, total_factors, 1, A, a1, b0, b1, &count, factors, exponents);
        printf("%llu\n", count);
    }
    return 0;
}