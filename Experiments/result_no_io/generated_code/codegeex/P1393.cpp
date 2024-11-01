#include <stdio.h>
#define MOD 998244353

// 快速幂函数，用于计算大数的幂次取模
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
    long long n, m, s_len;
    scanf("%lld %lld %lld", &n, &m, &s_len);

    long long a[s_len];
    for (int i = 0; i < s_len; i++) {
        scanf("%lld", &a[i]);
    }

    // 计算总的可能性数量，即 m^n
    long long total = mod_pow(m, n, MOD);

    // 计算包含名字 S 的可能性数量
    long long count = 1;
    for (int i = 0; i < s_len; i++) {
        count = (count * a[i]) % MOD;
    }

    // 计算概率，并对结果取模
    long long probability = count * mod_pow(total, MOD - 2, MOD) % MOD;

    printf("%lld\n", probability);
    return 0;
}