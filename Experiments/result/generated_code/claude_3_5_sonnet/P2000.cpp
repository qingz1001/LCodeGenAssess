#include <stdio.h>
#include <string.h>

#define MOD 998244353

char n[100001];
int len;

long long quick_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    scanf("%s", n);
    len = strlen(n);

    long long kkksc03 = 1, lzn = 1;

    // kkksc03
    kkksc03 = kkksc03 * ((quick_pow(6, len) - 1) * quick_pow(5, MOD - 2) % MOD + 1) % MOD; // 金
    kkksc03 = kkksc03 * 10 % MOD; // 木
    kkksc03 = kkksc03 * 6 % MOD; // 水
    kkksc03 = kkksc03 * ((quick_pow(4, len) - 1) * quick_pow(3, MOD - 2) % MOD + 1) % MOD; // 火
    kkksc03 = kkksc03 * 8 % MOD; // 土

    // lzn
    lzn = lzn * ((quick_pow(2, len) - 1) * quick_pow(1, MOD - 2) % MOD + 1) % MOD; // 金
    lzn = lzn * 2 % MOD; // 木
    lzn = lzn * ((quick_pow(8, len) - 1) * quick_pow(7, MOD - 2) % MOD + 1) % MOD; // 水
    lzn = lzn * ((quick_pow(10, len) - 1) * quick_pow(9, MOD - 2) % MOD + 1) % MOD; // 火
    lzn = lzn * 4 % MOD; // 土

    printf("%lld\n", (kkksc03 + lzn - 1 + MOD) % MOD);

    return 0;
}