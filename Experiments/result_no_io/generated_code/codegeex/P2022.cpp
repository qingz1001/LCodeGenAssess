#include <stdio.h>
#include <math.h>

long long q(long long N, long long K) {
    long long x = (long long)log10(K);
    long long ans = 0;
    ans += K * (x + 1);
    ans -= (x * (x + 1)) / 2;
    ans -= x;
    return ans;
}

int main() {
    long long K, M;
    scanf("%lld%lld", &K, &M);

    long long low = 1, high = 1000000000000LL;
    while (low < high) {
        long long mid = (low + high) / 2;
        if (q(mid, K) < M) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (q(low, K) == M) {
        printf("%lld\n", low);
    } else {
        printf("0\n");
    }

    return 0;
}