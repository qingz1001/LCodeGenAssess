#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 15
#define MAXMASK (1<<15)

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int left_edges[MAXN];
    for(int i=0;i<n;i++) left_edges[i]=0;
    for(int i=0;i<m;i++){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int a, b;
            scanf("%d %d", &a, &b);
            left_edges[a-1] |= (1 << (b-1));
        }
        else if(t ==1){
            int a1, b1, a2, b2;
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            // Do not include type1 edges
        }
        else if(t ==2){
            int a1, b1, a2, b2;
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            left_edges[a1-1] |= (1 << (b1-1));
            left_edges[a2-1] |= (1 << (b2-1));
        }
    }
    long long dp_prev[MAXMASK];
    long long dp_curr[MAXMASK];
    memset(dp_prev, 0, sizeof(dp_prev));
    memset(dp_curr, 0, sizeof(dp_curr));
    dp_prev[0] = 1;
    for(int i=0;i<n;i++){
        memset(dp_curr, 0, sizeof(dp_curr));
        for(int mask=0; mask < (1<<n); mask++){
            if(dp_prev[mask] ==0) continue;
            int available = left_edges[i] & (~mask);
            for(int j=0; j<n; j++){
                if(available & (1<<j)){
                    int new_mask = mask | (1<<j);
                    dp_curr[new_mask] = (dp_curr[new_mask] + dp_prev[mask]) % MOD;
                }
            }
        }
        // Swap dp_prev and dp_curr
        for(int mask=0; mask < (1<<n); mask++) dp_prev[mask] = dp_curr[mask];
    }
    printf("%lld\n", dp_prev[(1<<n)-1] % MOD);
    return 0;
}