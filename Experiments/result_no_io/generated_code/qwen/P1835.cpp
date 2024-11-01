#include <stdio.h>
#include <stdbool.h>

#define MAXN 1000005

bool is_prime[MAXN];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int count_primes_in_range(int L, int R) {
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (is_prime[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    
    // Assuming R - L + 1 <= 10^6, we can safely use the maximum value of R
    sieve(R);
    
    int result = count_primes_in_range(L, R);
    printf("%d\n", result);
    
    return 0;
}