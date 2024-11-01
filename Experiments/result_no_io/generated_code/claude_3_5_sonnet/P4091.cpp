#include <stdio.h>
#define MOD 998244353
#define MAXN 100005

long long S[MAXN][205];
long long pow2[MAXN], fact[MAXN];

void precompute(int n) {
    int i, j;
    
    // 预处理阶乘
    fact[0] = 1;
    for (i = 1; i <= 200; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    // 预处理2的幂
    pow2[0] = 1;
    for (i = 1; i <= n; i++) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }
    
    // 计算斯特林数
    for (i = 0; i <= n; i++) {
        S[i][i] = 1;
        for (j = 1; j <= i && j <= 200; j++) {
            S[i][j] = (j * S[i-1][j] + S[i-1][j-1]) % MOD;
        }
    }
}

long long solve(int n) {
    long long result = 0;
    int i, j;
    
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= i && j <= 200; j++) {
            result = (result + S[i][j] * pow2[j] % MOD * fact[j] % MOD) % MOD;
        }
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    precompute(n);
    printf("%lld\n", solve(n));
    
    return 0;
}