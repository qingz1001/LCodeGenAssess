#include <stdio.h>
#include <stdbool.h>

#define MAXN 500
#define MOD p

int n, p;
int dp[MAXN][MAXN];
bool is_prime[MAXN];
int primes[MAXN], prime_count = 0;

void sieve() {
    for (int i = 2; i <= n; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[prime_count++] = i;
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    sieve();

    dp[0][0] = 1;

    for (int i = 0; i < prime_count; i++) {
        for (int j = (1 << 8) - 1; j >= 0; j--) {
            for (int k = (1 << 8) - 1; k >= 0; k--) {
                if (dp[j][k] == 0) continue;
                int new_j = j, new_k = k;
                for (int x = primes[i]; x <= n; x *= primes[i]) {
                    if (j & (1 << (x - 2))) new_j |= (1 << (x - 2));
                    if (k & (1 << (x - 2))) new_k |= (1 << (x - 2));
                }
                dp[new_j][k] = (dp[new_j][k] + dp[j][k]) % MOD;
                dp[j][new_k] = (dp[j][new_k] + dp[j][k]) % MOD;
            }
        }
    }

    int result = 0;
    for (int j = 0; j < (1 << 8); j++) {
        for (int k = 0; k < (1 << 8); k++) {
            if ((j & k) == 0) {
                result = (result + dp[j][k]) % MOD;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}