#include <stdio.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    // Calculate the number of possible sequences
    long long possible_sequences = M;
    for (int i = 1; i < K - 1; i++) {
        possible_sequences = (possible_sequences * (M - i)) % P;
    }

    // Calculate the number of possible starting prices
    long long possible_starting_prices = (N - M * (K - 1) + 1) % P;

    // Calculate the final result
    long long result = (possible_sequences * possible_starting_prices) % P;

    printf("%lld\n", result);
    return 0;
}