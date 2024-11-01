#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAXN 100005

typedef long long ll;

ll S[MAXN][MAXN];
ll factorial[MAXN];
ll power_of_two[MAXN];

void preprocess(int n) {
    // Precompute factorials and powers of two
    factorial[0] = 1;
    power_of_two[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;
        power_of_two[i] = power_of_two[i - 1] * 2 % MOD;
    }

    // Precompute Stirling numbers of the second kind
    for (int i = 0; i <= n; i++) {
        S[i][0] = 0;
        S[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            S[i][j] = (j * S[i - 1][j] % MOD + S[i - 1][j - 1]) % MOD;
        }
    }
}

ll solve(int n) {
    ll result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            result = (result + S[i][j] * power_of_two[j] % MOD * factorial[j] % MOD) % MOD;
        }
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    preprocess(n);
    ll result = solve(n);

    printf("%lld\n", result);

    return 0;
}