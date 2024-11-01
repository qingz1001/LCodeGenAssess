#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define MAX_N 100005
#define INF 1000000000000000001LL

typedef long long ll;

ll dp[MAX_N];
ll prev_idx[MAX_N];
ll power_cache[11][3000006]; // P up to 10 and |diff| up to 3e6

int main(){
    int T;
    scanf("%d", &T);
    // Precompute powers
    for(int p=1; p<=10; p++){
        for(int d=0; d<=3000000; d++){
            ll res=1;
            for(int i=0;i<p;i++) res *= d;
            power_cache[p][d] = res > INF ? INF : res;
        }
    }
    while(T--){
        int N, L, P;
        scanf("%d %d %d", &N, &L, &P);
        char sentences[N][31];
        int lengths[N];
        for(int i=0;i<N;i++){
            scanf("%s", sentences[i]);
            lengths[i] = strlen(sentences[i]);
        }
        // Prefix sums
        ll prefix_sum[N+1];
        prefix_sum[0]=0;
        for(int i=1;i<=N;i++) prefix_sum[i] = prefix_sum[i-1] + lengths[i-1];
        // Initialize DP
        for(int i=0;i<=N;i++) dp[i] = INF;
        dp[0] = 0;
        // DP
        for(int i=1;i<=N;i++){
            // Try all possible j from i-1 downto 0
            // To optimize, limit the number of j checked
            for(int j=i-1; j>=0 && (prefix_sum[i] - prefix_sum[j] + (i-j-1)) <= L + 100; j--){
                ll total = prefix_sum[i] - prefix_sum[j] + (i-j-1);
                ll diff = total > L ? total - L : L - total;
                if(diff > 3000000) continue;
                ll cost = power_cache[P][diff];
                if(dp[j] + cost < dp[i]){
                    dp[i] = dp[j] + cost;
                    prev_idx[i] = j;
                }
            }
        }
        if(dp[N] > 1000000000000000000LL){
            printf("Too hard to arrange\n");
        }
        else{
            printf("%lld\n", dp[N]);
            // Reconstruct the path
            int splits[N+1];
            int cnt=0;
            ll idx = N;
            while(idx > 0){
                splits[cnt++] = idx;
                idx = prev_idx[idx];
            }
            for(int i=cnt-1;i>=0;i--){
                int start = prev_idx[splits[i]];
                for(int j=start; j < splits[i]; j++){
                    printf("%s", sentences[j]);
                    if(j < splits[i]-1) printf(" ");
                }
                printf("\n");
            }
        }
        // Print separator
        printf("--------------------\n");
    }
    return 0;
}