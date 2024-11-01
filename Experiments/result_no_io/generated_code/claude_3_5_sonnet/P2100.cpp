#include <stdio.h>
#define MOD 100000000

long long fastPow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    char n[1001];
    scanf("%s", n);
    
    long long dp[3] = {1, 0, 0};
    long long new_dp[3];
    
    for (int i = 0; n[i]; i++) {
        new_dp[0] = dp[1];
        new_dp[1] = (dp[0] + dp[2]) % MOD;
        new_dp[2] = dp[1];
        
        for (int j = 0; j < 3; j++) {
            dp[j] = new_dp[j];
        }
    }
    
    long long result = (dp[0] + dp[1] + dp[2]) % MOD;
    
    if (result == 0) {
        printf("0\n");
    } else {
        printf("%lld\n", result);
    }
    
    return 0;
}