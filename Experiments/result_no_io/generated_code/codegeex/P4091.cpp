#include <stdio.h>
#define MOD 998244353

// 快速幂计算 (a^b) % mod
long long mod_pow(long long a, long long b, long long mod) {
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

// 计算阶乘并取模
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact = (fact * i) % MOD;
    }
    return fact;
}

int main() {
    int n;
    scanf("%d", &n);

    long long S[100005][20] = {0}; // 存储2类斯特林数
    S[0][0] = 1; // 边界条件

    // 计算第二类斯特林数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            S[i][j] = (j * S[i-1][j] + S[i-1][j-1]) % MOD;
        }
    }

    long long result = 0;
    long long fact2 = 1; // 存储2^j * j!

    // 计算f(n)
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            fact2 = (mod_pow(2, j, MOD) * factorial(j)) % MOD;
            result = (result + S[i][j] * fact2) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}