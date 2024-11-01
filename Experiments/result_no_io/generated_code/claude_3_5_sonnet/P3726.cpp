#include <stdio.h>
#include <string.h>

#define MOD 1000000000

long long dp[2][100005];
long long C[100005];

void init(int n) {
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i] = C[i-1] * (n-i+1) / i % MOD;
    }
}

int main() {
    long long a, b;
    int k;
    
    while (scanf("%lld %lld %d", &a, &b, &k) != EOF) {
        memset(dp, 0, sizeof(dp));
        
        int diff = a - b;
        long long ans = 0;
        
        init(b);
        
        dp[0][0] = 1;
        int cur = 0, nxt = 1;
        
        for (int i = 0; i <= diff; i++) {
            memset(dp[nxt], 0, sizeof(dp[nxt]));
            for (int j = 0; j <= b; j++) {
                dp[nxt][j] = (dp[cur][j] + (j > 0 ? dp[cur][j-1] : 0)) % MOD;
            }
            cur ^= 1;
            nxt ^= 1;
        }
        
        for (int i = 0; i <= b; i++) {
            for (int j = 0; j < i; j++) {
                ans = (ans + dp[cur][i] * C[j]) % MOD;
            }
        }
        
        int mod = 1;
        for (int i = 0; i < k; i++) {
            mod *= 10;
        }
        
        printf("%0*lld\n", k, ans % mod);
    }
    
    return 0;
}