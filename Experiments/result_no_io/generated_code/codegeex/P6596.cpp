#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll n, m;

ll factorial(int n) {
    ll result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

ll combinations(int n, int k) {
    if (k > n) return 0;
    ll numerator = 1, denominator = 1;
    for (int i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }
    return (numerator * (denominator % MOD)) % MOD;
}

ll countGraphs(int n, int m) {
    ll result = 0;
    for (int i = 0; i <= m; i++) {
        ll waysToConnect = combinations(n * (n - 1) / 2, i);
        ll waysToFormGraphs = combinations(factorial(n), n);
        result = (result + (waysToConnect * waysToFormGraphs) % MOD) % MOD;
    }
    return result;
}

int main() {
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", countGraphs(n, m));
    return 0;
}