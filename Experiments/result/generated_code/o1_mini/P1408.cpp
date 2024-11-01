#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute GCD
long long gcd_func(long long a, long long b){
    while(b){
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Sieve of Eratosthenes to generate primes up to max_limit
int sieve_limit = 5000;
int sieve[5001];
int primes[669]; // Number of primes up to 5000 is 669
int prime_count = 0;

void generate_primes(){
    for(int i=0;i<=sieve_limit;i++) sieve[i]=1;
    sieve[0]=sieve[1]=0;
    for(int p=2;p*p<=sieve_limit;p++){
        if(sieve[p]){
            for(int multiple=p*p; multiple<=sieve_limit; multiple+=p){
                sieve[multiple]=0;
            }
        }
    }
    for(int p=2;p<=sieve_limit;p++) if(sieve[p]) primes[prime_count++] = p;
}

// Function to compute sum of prime factors with multiplicity
long long sum_prime_factors(long long g){
    if(g == 1) return 0;
    long long sum = 0;
    for(int i=0;i<prime_count && primes[i]*primes[i] <= g;i++){
        while(g % primes[i] == 0){
            sum += primes[i];
            g /= primes[i];
        }
    }
    if(g > 1){
        sum += g;
    }
    return sum;
}

int main(){
    generate_primes();
    int n;
    scanf("%d", &n);
    if(n <= 0){
        printf("0\n");
        return 0;
    }
    long long *A = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &A[i]);
    long long total = 0;
    for(int i=0;i<n-1;i++){
        long long g = gcd_func(A[i], A[i+1]);
        total += sum_prime_factors(g);
    }
    printf("%lld\n", total);
    free(A);
    return 0;
}