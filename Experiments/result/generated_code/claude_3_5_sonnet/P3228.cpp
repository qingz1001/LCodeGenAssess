#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXK 1000005

long long dp[MAXK];
long long sum[MAXK];

long long fast_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    long long N, K, M, P;
    scanf("%lld %lld %lld %lld", &N, &K, &M, &P);

    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    for (int i = 1; i <= N && i <= M * (K - 1); i++) {
        dp[1] = 1;
        sum[1] = 1;
    }

    for (int i = 2; i <= K; i++) {
        for (int j = i; j <= N && j <= M * (i - 1); j++) {
            int left = (j - M > 0) ? j - M : 0;
            dp[i] = (sum[i-1] - (left > 0 ? sum[left-1] : 0) + P) % P;
            sum[j] = (sum[j-1] + dp[i]) % P;
        }
    }

    long long result = sum[N] - (N > M*(K-1) ? sum[M*(K-1)] : 0);
    result = (result % P + P) % P;

    printf("%lld\n", result);

    return 0;
}