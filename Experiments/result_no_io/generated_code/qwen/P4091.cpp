#include <stdio.h>
#define MOD 998244353

typedef long long ll;

ll factorial[100005];
ll stirling[100005][100005];

void precompute() {
    factorial[0] = 1;
    for (int i = 1; i <= 100000; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }

    stirling[0][0] = 1;
    for (int i = 1; i <= 100000; ++i) {
        stirling[i][i] = 1;
        stirling[i][0] = 0;
        for (int j = 1; j < i; ++j) {
            stirling[i][j] = (stirling[i - 1][j - 1] + (ll)j * stirling[i - 1][j]) % MOD;
        }
    }
}

ll power(ll base, int exp) {
    if (exp == 0) return 1;
    ll half = power(base, exp / 2);
    ll result = half * half % MOD;
    if (exp % 2 == 1) result = result * base % MOD;
    return result;
}

ll calculateF(int n) {
    ll result = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            ll term = stirling[i][j] * power(2, j) % MOD * factorial[j] % MOD;
            result = (result + term) % MOD;
        }
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    precompute();
    printf("%lld\n", calculateF(n));

    return 0;
}