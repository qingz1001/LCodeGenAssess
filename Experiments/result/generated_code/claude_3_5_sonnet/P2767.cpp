#include <stdio.h>

#define MOD 10007
#define MAXN 128

int dp[MAXN];

int pow_mod(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            int temp = pow_mod(dp[j], m);
            dp[i] = (dp[i] + dp[i-j-1] * temp) % MOD;
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}