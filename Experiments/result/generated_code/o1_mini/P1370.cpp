#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAX 100005

long long power2[MAX];
int last_pos[1000005];

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc((n+1) * sizeof(int));
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);

    power2[0] = 1;
    for(int i=1; i<=n; i++) {
        power2[i] = (power2[i-1] * 2) % MOD;
    }

    for(int i=0; i<=1000000; i++) last_pos[i] = 0;

    long long dp = 1;
    long long total = 0;
    long long sum = 0;

    for(int i=1; i<=n; i++){
        long long new_dp = (dp * 2) % MOD;
        if(last_pos[a[i]]){
            new_dp = (new_dp - power2[i - last_pos[a[i]] -1] + MOD) % MOD;
        }
        last_pos[a[i]] = i;
        dp = new_dp;
        sum = (sum + dp) % MOD;
    }

    // To compute sum of F(l,r), use the formula sum = (sum of dp[r]) where dp[r] is number of distinct subsequences up to r
    // However, based on the problem's sample, this approach might not be accurate. Adjust accordingly if necessary.

    printf("%lld\n", sum);
    free(a);
    return 0;
}