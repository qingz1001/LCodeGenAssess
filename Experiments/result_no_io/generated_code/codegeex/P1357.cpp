#include <stdio.h>

#define MOD 1000000007

long long n, m, k;

// 计算组合数 C(n, k)
long long comb(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = (res * (n - i + 1) % MOD * pow(i, MOD - 2, MOD)) % MOD;
    }
    return res;
}

// 快速幂计算 a^b % MOD
long long pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

// 计算符合规则的花园种数
long long countGardens() {
    long long totalPatterns = pow(2, m, MOD); // 总的2^m种排列
    long long validPatterns = 0;
    for (int i = 0; i <= k; ++i) {
        validPatterns = (validPatterns + comb(m, i) * pow(2, m - i - 1, MOD)) % MOD;
    }
    return (totalPatterns - validPatterns + MOD) % MOD;
}

int main() {
    scanf("%lld %lld %lld", &n, &m, &k);
    printf("%lld\n", countGardens());
    return 0;
}