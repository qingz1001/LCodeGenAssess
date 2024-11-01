#include <stdio.h>
#include <math.h>

#define MOD 1000000007

// 计算最大公约数
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 计算组合数 C(n, k)
long long comb(long long n, long long k) {
    if (k > n) return 0;
    long long res = 1;
    for (long long i = 1; i <= k; i++) {
        res = res * (n - i + 1) % MOD;
        res = res * pow(i, MOD - 2, MOD) % MOD;
    }
    return res;
}

// 快速幂计算 a^b % mod
long long pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, a;
        scanf("%lld%lld", &n, &a);

        // 计算满足条件的珠子数量
        long long count = comb(3 * a - 1, 3) - comb(3 * a - 1, 1) + MOD;

        // 计算项链数量
        long long result = pow(count, n, MOD);

        printf("%lld\n", result);
    }
    return 0;
}