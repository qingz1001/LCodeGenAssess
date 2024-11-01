#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_M 201
#define MAX_K 201

typedef long long ll;

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char A[1001], B[201];
    scanf("%s %s", A, B);
    
    // Initialize DP arrays
    ll dp[MAX_M][MAX_K][2];
    ll dp_next[MAX_M][MAX_K][2];
    memset(dp, 0, sizeof(dp));
    memset(dp_next, 0, sizeof(dp_next));
    
    dp[0][0][0] = 1;
    
    for(int i = 0; i < n; i++){
        // Reset dp_next
        memset(dp_next, 0, sizeof(dp_next));
        for(int j = 0; j <= m; j++){
            for(int t = 0; t <= k; t++){
                for(int c = 0; c < 2; c++){
                    if(dp[j][t][c] == 0) continue;
                    
                    // Option 1: Skip A[i]
                    dp_next[j][t][c] = (dp_next[j][t][c] + dp[j][t][c]) % MOD;
                    
                    // Option 2: Use A[i] if it matches B[j]
                    if(j < m && A[i] == B[j]){
                        if(c == 1){
                            dp_next[j+1][t][1] = (dp_next[j+1][t][1] + dp[j][t][c]) % MOD;
                        }
                        else{
                            if(t + 1 <= k){
                                dp_next[j+1][t+1][1] = (dp_next[j+1][t+1][1] + dp[j][t][c]) % MOD;
                            }
                        }
                    }
                }
            }
        }
        // Swap dp and dp_next
        memcpy(dp, dp_next, sizeof(dp));
    }
    
    ll result = 0;
    if(k <= m){
        result = (dp[m][k][0] + dp[m][k][1]) % MOD;
    }
    printf("%lld\n", result);
}