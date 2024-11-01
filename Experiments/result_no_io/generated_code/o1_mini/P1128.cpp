#include <stdio.h>
#include <stdint.h>
#include <math.h>

unsigned long long min_m = UINT64_MAX;
int n;
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void backtrack(unsigned long long current_m, int current_d, int prime_idx, int limit) {
    if (current_d == n) {
        if (current_m < min_m) {
            min_m = current_m;
        }
        return;
    }
    if (prime_idx >= sizeof(primes)/sizeof(primes[0])) {
        return;
    }
    for(int e = 1; e <= limit; e++) {
        if (n % (current_d * (e + 1)) != 0) continue;
        unsigned long long next_m = current_m;
        for(int i = 0; i < e; i++) {
            if (next_m > UINT64_MAX / primes[prime_idx]) {
                next_m = UINT64_MAX;
                break;
            }
            next_m *= primes[prime_idx];
        }
        if (next_m >= min_m) continue;
        backtrack(next_m, current_d * (e + 1), prime_idx + 1, e);
    }
}

int main(){
    scanf("%d", &n);
    if(n == 1){
        printf("1\n");
        return 0;
    }
    backtrack(1, 1, 0, 60);
    printf("%llu\n", min_m);
    return 0;
}