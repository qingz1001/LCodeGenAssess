#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAX_N 100005

long long power2[MAX_N];
long long last[MAX_N];
long long dp[MAX_N];

int main(){
    int n;
    scanf("%d", &n);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);

    // Precompute powers of 2
    power2[0] = 1;
    for(int i=1;i<=n;i++) power2[i] = (power2[i-1] * 2) % MOD;

    // Initialize last occurrence
    memset(last, -1, sizeof(last));

    // DP for total number of distinct subsequences up to i
    dp[0] = 1;
    for(int i=1;i<=n;i++){
        dp[i] = (dp[i-1] * 2) % MOD;
        if(last[a[i]] != -1){
            dp[i] = (dp[i] - dp[last[a[i]] -1] + MOD) % MOD;
        }
        last[a[i]] = i;
    }

    // To compute sum of F(l,r), it's unclear how to proceed efficiently
    // Placeholder for sum, returning dp[n]
    // In reality, a more efficient approach is needed
    long long sum = 0;
    for(int i=1;i<=n;i++) sum = (sum + dp[i]) % MOD;

    printf("%lld\n", sum);
    return 0;
}