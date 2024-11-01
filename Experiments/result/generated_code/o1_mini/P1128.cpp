#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned long long primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
unsigned long long min_m = ULLONG_MAX;
unsigned long long target_n;
unsigned long long best_m = ULLONG_MAX;

void backtrack(int prime_idx, unsigned long long current_m, unsigned long long current_n, int max_exp) {
    if (current_n == target_n) {
        if (current_m < best_m) {
            best_m = current_m;
        }
        return;
    }
    if (prime_idx >= 15) return;
    if (current_n > target_n) return;

    for (int exp = 1; exp <= max_exp; exp++) {
        if (current_n * (exp + 1) > target_n) break;
        unsigned long long next_m = current_m;
        for (int i = 0; i < exp; i++) {
            if (next_m > best_m / primes[prime_idx]) {
                next_m = ULLONG_MAX;
                break;
            }
            next_m *= primes[prime_idx];
        }
        if (next_m == ULLONG_MAX) break;
        backtrack(prime_idx + 1, next_m, current_n * (exp + 1), exp);
    }
    // Also consider not using the current prime
    backtrack(prime_idx + 1, current_m, current_n, 0);
}

int main(){
    scanf("%llu", &target_n);
    best_m = ULLONG_MAX;
    backtrack(0, 1, 1, 60);
    printf("%llu\n", best_m);
    return 0;
}