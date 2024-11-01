#include <stdio.h>
#include <stdbool.h>

#define MAXN 500
#define MAXP 30

int n, p;
int dp[1 << MAXP][1 << MAXP];
int primes[MAXP], prime_count = 0;
int factor[MAXN];

void sieve() {
    bool is_prime[MAXN];
    for (int i = 2; i < MAXN; i++) is_prime[i] = true;
    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
            for (int j = i * i; j < MAXN; j += i) is_prime[j] = false;
        }
    }
}

void factorize() {
    for (int i = 2; i <= n; i++) {
        int x = i;
        for (int j = 0; j < prime_count && primes[j] <= x; j++) {
            if (x % primes[j] == 0) {
                factor[i] |= (1 << j);
                while (x % primes[j] == 0) x /= primes[j];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    sieve();
    factorize();

    dp[0][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int g = (1 << prime_count) - 1; g >= 0; g--) {
            for (int w = (1 << prime_count) - 1; w >= 0; w--) {
                if ((g & w) == 0) {
                    if ((factor[i] & w) == 0) {
                        dp[g | factor[i]][w] = (dp[g | factor[i]][w] + dp[g][w]) % p;
                    }
                    if ((factor[i] & g) == 0) {
                        dp[g][w | factor[i]] = (dp[g][w | factor[i]] + dp[g][w]) % p;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int g = 0; g < (1 << prime_count); g++) {
        for (int w = 0; w < (1 << prime_count); w++) {
            if ((g & w) == 0) {
                result = (result + dp[g][w]) % p;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}