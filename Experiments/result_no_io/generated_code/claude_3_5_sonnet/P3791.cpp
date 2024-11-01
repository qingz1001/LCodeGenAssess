#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 1000001

long long d[MAXN];

void init() {
    memset(d, 0, sizeof(d));
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            d[j]++;
        }
    }
}

long long solve(long long n, long long m, long long x) {
    long long ans = 0;
    for (long long i = 0; i <= n && i < MAXN; i++) {
        for (long long j = 0; j <= m && j < MAXN; j++) {
            long long val = i ^ j ^ x;
            if (val < MAXN) {
                ans = (ans + d[val]) % MOD;
            }
        }
    }
    return ans;
}

int main() {
    long long n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    
    init();
    
    printf("%lld\n", solve(n, m, x));
    
    return 0;
}