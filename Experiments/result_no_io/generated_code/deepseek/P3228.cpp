#include <stdio.h>

typedef long long ll;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
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
    ll N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    // 计算可能的股价种数
    ll total_ways = mod_pow(M, K - 1, P);
    ll sum_diff = (M * (M + 1) / 2) % P;
    ll possible_ways = (total_ways * sum_diff) % P;
    ll result = (N % P * total_ways % P - possible_ways + P) % P;

    printf("%lld\n", result);

    return 0;
}