#include <stdio.h>

#define MOD 998244353

long long n, m, x;
long long cnt[1000000000];

int main() {
    scanf("%lld%lld%lld", &n, &m, &x);
    
    long long total = 0;
    
    for (long long i = 0; i <= n; i++) {
        for (long long j = 0; j <= m; j++) {
            long long result = i ^ j ^ x;
            cnt[result]++;
        }
    }
    
    for (long long i = 0; i < 1000000000; i++) {
        if (cnt[i] > 0) {
            long long num = i;
            long long divisor_count = 0;
            for (long long j = 1; j * j <= num; j++) {
                if (num % j == 0) {
                    divisor_count++;
                    if (j * j != num) {
                        divisor_count++;
                    }
                }
            }
            total = (total + cnt[i] * divisor_count) % MOD;
        }
    }
    
    printf("%lld\n", total);
    
    return 0;
}