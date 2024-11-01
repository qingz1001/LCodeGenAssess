#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000000000000LL

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *x = malloc((n+1) * sizeof(long long));
    for(int i=1;i<=n;i++) scanf("%lld", &x[i]);
    
    long long *DP_prev = malloc((n+1) * sizeof(long long));
    long long *DP_curr = malloc((n+1) * sizeof(long long));
    
    for(int i=0;i<=n;i++) DP_prev[i] = INF;
    DP_prev[0] = 0;
    
    for(int k=1;k<=m;k++){
        DP_curr[0] = INF;
        long long min_prev = DP_prev[0] - x[1];
        for(int i=1;i<=n;i++){
            if(i-1 >=0){
                long long current = DP_prev[i-1] - x[i];
                if(current < min_prev){
                    min_prev = current;
                }
            }
            DP_curr[i] = x[i] + min_prev;
        }
        // Swap DP_prev and DP_curr
        long long *temp = DP_prev;
        DP_prev = DP_curr;
        DP_curr = temp;
    }
    
    printf("%lld\n", DP_prev[n]);
    
    free(x);
    free(DP_prev);
    free(DP_curr);
    return 0;
}