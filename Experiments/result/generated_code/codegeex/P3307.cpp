#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        res = res * (n - i + 1) / i;
    }
    return res;
}

// 计算欧拉函数 φ(n)
long long euler(long long n) {
    long long res = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

// 计算项链的数量
long long countBeads(long long n, long long a) {
    long long res = 0;
    for (long long i = 1; i * i <= a; i++) {
        if (a % i == 0) {
            for (long long j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    long long x = j, y = i / j;
                    if (gcd(x, gcd(y, a / i)) == 1) {
                        long long m = n / 3;
                        res = (res + comb(m, x) * comb(m, y) % MOD) % MOD;
                    }
                }
            }
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, a;
        scanf("%lld%lld", &n, &a);
        long long ans = countBeads(n, a);
        printf("%lld\n", ans);
    }
    return 0;
}