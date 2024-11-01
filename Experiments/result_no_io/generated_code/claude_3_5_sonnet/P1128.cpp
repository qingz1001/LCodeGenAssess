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

int main() {
    sieve();
    int n;
    scanf("%d", &n);
    
    int result = 1;
    int factors = 1;
    int index = 0;
    
    while (factors < n) {
        result *= primes[index];
        factors *= 2;
        index++;
    }
    
    while (factors > n) {
        while (result % primes[index - 1] == 0 && factors > n) {
            result /= primes[index - 1];
            factors = factors / 2 + 1;
        }
        index--;
    }
    
    printf("%d\n", result);
    
    return 0;
}