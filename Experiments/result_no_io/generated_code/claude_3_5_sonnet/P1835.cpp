#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 1000001

bool is_prime[MAXN];

void sieve(int L, int R) {
    for (int i = 0; i <= R - L; i++) {
        is_prime[i] = true;
    }
    
    if (L == 1) is_prime[0] = false;
    
    for (long long i = 2; i * i <= R; i++) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
            is_prime[j - L] = false;
        }
    }
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    
    sieve(L, R);
    
    int count = 0;
    for (int i = 0; i <= R - L; i++) {
        if (is_prime[i]) {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}