#include <stdio.h>
#include <math.h>

#define MAX_N 1000000000000000001LL

long long primes[70];
int prime_count = 0;

void sieve() {
    bool is_prime[100000] = {0};
    for (int i = 2; i < 100000; i++) {
        if (!is_prime[i]) {
            primes[prime_count++] = i;
            for (int j = i * i; j < 100000; j += i) {
                is_prime[j] = true;
            }
        }
    }
}

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    sieve();
    
    int T;
    scanf("%d", &T);
    
    long long n;
    while (T--) {
        scanf("%lld", &n);
        
        long long f = 0;
        for (int i = 0; i < prime_count; i++) {
            long long p = primes[i];
            long long power = 1;
            long long count = 0;
            
            while (power <= n) {
                count++;
                power *= p;
            }
            
            if (count > 1) {
                f += count * (count - 1) / 2;
            }
        }
        
        double result = (double)f / n;
        printf("%.14lf\n", result);
    }
    
    return 0;
}