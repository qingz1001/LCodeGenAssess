#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

typedef long long ll;

ll S[MAXN][MAXN];
ll fact[MAXN];
ll pow2[MAXN];

void preprocess(int n) {
    // 计算第二类斯特林数
    S[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        S[i][0] = 0;
        for (int j = 1; j <= i; j++) {
            S[i][j] = (j * S[i-1][j] % MOD + S[i-1][j-1]) % MOD;
        }
    }

    // 计算阶乘
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }

    // 计算2的幂
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
    }
}

ll solve(int n) {
    ll result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            result = (result + S[i][j] * pow2[j] % MOD * fact[j] % MOD) % MOD;
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