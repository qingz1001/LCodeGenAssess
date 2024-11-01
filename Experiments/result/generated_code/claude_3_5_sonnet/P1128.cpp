#include <stdio.h>
#include <stdbool.h>

#define MAX_N 50001

int primes[MAX_N];
int prime_count = 0;

void sieve() {
    bool is_prime[MAX_N] = {false};
    for (int i = 2; i < MAX_N; i++) {
        if (!is_prime[i]) {
            primes[prime_count++] = i;
            for (int j = i * i; j < MAX_N; j += i) {
                is_prime[j] = true;
            }
        }
    }
}

long long solve(int n) {
    long long result = 1;
    int factors = 1;
    int prime_index = 0;
    
    while (factors < n) {
        result *= primes[prime_index];
        factors *= 2;
        prime_index++;
    }
    
    while (factors > n) {
        prime_index--;
        factors /= 2;
        result /= primes[prime_index];
        factors *= (primes[prime_index] - 1);
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    sieve();
    long long result = solve(n);
    
    printf("%lld\n", result);
    
    return 0;
}