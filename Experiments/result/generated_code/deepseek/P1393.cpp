#include <stdio.h>
#include <string.h>

#define MOD 998244353

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
    int n, m, s_len;
    scanf("%d %d %d", &n, &m, &s_len);
    int S[s_len];
    for (int i = 0; i < s_len; i++) {
        scanf("%d", &S[i]);
    }

    // Calculate the total number of possible strings of length n
    long long total_strings = mod_pow(m, n, MOD);

    // Calculate the number of strings that do not contain the name S
    long long no_name_strings = mod_pow(m, n - s_len, MOD);

    // Calculate the probability of not containing the name S
    long long no_name_probability = (no_name_strings * mod_pow(total_strings, MOD - 2, MOD)) % MOD;

    // Calculate the probability of containing the name S
    long long name_probability = (1 - no_name_probability + MOD) % MOD;

    printf("%lld\n", name_probability);

    return 0;
}