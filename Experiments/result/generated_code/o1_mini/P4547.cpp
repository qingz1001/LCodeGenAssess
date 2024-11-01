#include <stdio.h>
#include <string.h>
#define MOD 1000000007
#include <stdint.h>

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    // Initialize adjacency matrix
    unsigned short adj[15];
    for(int i=0;i<n;i++) adj[i]=0;
    // To mark edges from type1 groups
    for(int i=0;i<m;i++){
        int t, a1, b1, a2, b2;
        scanf("%d", &t);
        if(t == 0){
            scanf("%d %d", &a1, &b1);
            a1--, b1--;
            // Type0, keep the edge
            adj[a1] |= (1<<b1);
        }
        else if(t ==1){
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            a1--, b1--, a2--, b2--;
            // Type1, remove these edges by not adding them
            // Do nothing
        }
        else{
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            a1--, b1--, a2--, b2--;
            // Type2, keep the edges
            adj[a1] |= (1<<b1);
            adj[a2] |= (1<<b2);
        }
    }
    // DP for counting perfect matchings
    int size = 1<<n;
    ll dp[size];
    memset(dp, 0, sizeof(dp));
    dp[0] =1;
    for(int mask=0; mask<(1<<n); mask++){
        // Count number of set bits to determine the current left node
        int k=0;
        int temp = mask;
        while(temp){
            temp &= temp-1;
            k++;
        }
        if(k >=n) continue;
        for(int j=0; j<n; j++){
            if( (adj[k] & (1<<j)) && !(mask & (1<<j)) ){
                int new_mask = mask | (1<<j);
                dp[new_mask] = (dp[new_mask] + dp[mask]) % MOD;
            }
        }
    }
    ll total = dp[(1<<n)-1];
    printf("%lld\n", total);
}