#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

long long S[MAXN][2], pow2[MAXN], fact[MAXN];

void precompute(int n) {
    pow2[0] = fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
        fact[i] = (fact[i-1] * i) % MOD;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    precompute(n);
    
    S[0][0] = 1;
    long long result = 1; // f(0) = 1
    
    for (int i = 1; i <= n; i++) {
        int curr = i & 1;
        int prev = 1 - curr;
        
        memset(S[curr], 0, sizeof(S[curr]));
        S[curr][i] = 1;
        
        long long sum = 1; // S(i,i) * 2^i * i!
        for (int j = 1; j < i; j++) {
            S[curr][j] = (j * S[prev][j] + S[prev][j-1]) % MOD;
            sum = (sum + S[curr][j] * pow2[j] % MOD * fact[j] % MOD) % MOD;
        }
        
        result = (result + sum) % MOD;
    }
    
    printf("%lld\n", result);
    return 0;
}