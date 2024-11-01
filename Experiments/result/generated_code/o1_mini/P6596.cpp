#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 51
#define MAXM 1275

long long comb[MAXN*(MAXN-1)/2 + 1][MAXN];
long long dp[MAXN][MAXM + 1];
long long power2[MAXN*(MAXN-1)/2 + 1];

// Function to compute combination nCk
long long C(int n, int k){
    if(k > n) return 0;
    return comb[n][k];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Initialize combination table
    for(int i=0;i<=n*(n-1)/2;i++){
        comb[i][0] = 1;
        for(int j=1; j<=i && j<=n; j++){
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
        }
    }
    
    // Initialize power of 2
    power2[0] = 1;
    for(int i=1;i<=n*(n-1)/2;i++) power2[i] = (power2[i-1] * 2) % MOD;
    
    // Initialize DP
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;
    
    for(int nodes=1; nodes<n; nodes++){
        for(int bridges=0; bridges<=m; bridges++){
            if(dp[nodes][bridges] == 0) continue;
            for(int add=1; add<=n - nodes; add++){
                if(nodes + add > n) break;
                for(int b=0; b <= bridges; b++){
                    if(b + 1 > m) continue;
                    dp[nodes + add][b + 1] = (dp[nodes + add][b + 1] + dp[nodes][bridges] * C(n - nodes -1, add -1)) % MOD;
                }
            }
        }
    }
    
    long long result = 0;
    for(int b=0; b<=m; b++) result = (result + dp[n][b]) % MOD;
    printf("%lld\n", result);
    return 0;
}