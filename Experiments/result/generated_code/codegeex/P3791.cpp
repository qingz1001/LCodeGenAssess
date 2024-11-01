#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

// 计算一个数的约数个数
int count_divisors(int num) {
    if (num == 0) return 0;
    int count = 0;
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            count++;
            if (i * i != num) count++;
        }
    }
    return count;
}

// 计算两个数的异或
ll xor(ll a, ll b) {
    return a ^ b;
}

// 计算一个数的二进制表示中1的个数
int count_bits(ll num) {
    int count = 0;
    while (num) {
        if (num & 1) count++;
        num >>= 1;
    }
    return count;
}

// 计算从0到n的数中，二进制表示中1的个数为k的数的个数
ll count_k_bits(ll n, int k) {
    ll count = 0;
    for (ll i = 0; i <= n; i++) {
        if (count_bits(i) == k) count++;
    }
    return count;
}

int main() {
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);

    ll result = 0;
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j <= m; j++) {
            ll xor_result = xor(i, xor(j, x));
            int divisors = count_divisors(xor_result);
            result = (result + divisors) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}