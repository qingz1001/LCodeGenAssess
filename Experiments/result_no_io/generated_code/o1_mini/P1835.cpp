#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef unsigned long long ull;

int main(){
    ull L, R;
    scanf("%llu %llu", &L, &R);
    
    ull limit = (ull)sqrt((double)R) + 1;
    // Sieve of Eratosthenes up to limit
    char *is_prime = (char*)malloc((limit + 1) * sizeof(char));
    memset(is_prime, 1, limit + 1);
    is_prime[0] = is_prime[1] = 0;
    for(ull p = 2; p * p <= limit; p++){
        if(is_prime[p]){
            for(ull multiple = p * p; multiple <= limit; multiple += p){
                is_prime[multiple] = 0;
            }
        }
    }
    
    // Collect primes up to sqrt(R)
    ull num_primes = 0;
    for(ull p = 2; p <= limit; p++) if(is_prime[p]) num_primes++;
    ull *primes = (ull*)malloc(num_primes * sizeof(ull));
    ull idx = 0;
    for(ull p = 2; p <= limit; p++) if(is_prime[p]) primes[idx++] = p;
    free(is_prime);
    
    // Segmented sieve
    ull size = R - L + 1;
    char *segment = (char*)malloc(size);
    memset(segment, 1, size);
    
    for(ull i = 0; i < num_primes; i++){
        ull p = primes[i];
        ull start = (L + p - 1) / p * p;
        if(start < p * p) start = p * p;
        for(ull multiple = start; multiple <= R; multiple += p){
            if(multiple >= L)
                segment[multiple - L] = 0;
        }
    }
    free(primes);
    
    if(L == 1){
        segment[0] = 0;
    }
    
    ull count = 0;
    for(ull i = 0; i < size; i++) if(segment[i]) count++;
    free(segment);
    
    printf("%llu\n", count);
    return 0;
}