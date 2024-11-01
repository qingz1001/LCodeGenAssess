#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAXN 128

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int dp[MAXN];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    int temp[MAXN], temp_new[MAXN];
    for(int k=1; k<=n; k++){
        memset(temp, 0, sizeof(temp));
        temp[0] = 1;
        for(int child=1; child<=m; child++){
            memset(temp_new, 0, sizeof(temp_new));
            for(int s=0; s<=k-1; s++){
                for(int i=0; i<=s; i++){
                    temp_new[s] += temp[s-i] * dp[i];
                    if(temp_new[s] >= MOD) temp_new[s] %= MOD;
                }
            }
            memcpy(temp, temp_new, sizeof(temp_new));
        }
        dp[k] = temp[k-1] % MOD;
    }
    printf("%d\n", dp[n]);
    return 0;
}