#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N;
    ll L;
    scanf("%d %lld", &N, &L);
    
    // Using 1-based indexing
    int *H = (int*)malloc((N+1) * sizeof(int));
    ll *W = (ll*)malloc((N+1) * sizeof(ll));
    for(int i=1;i<=N;i++) scanf("%d %lld", &H[i], &W[i]);
    
    // DP array
    ll *dp = (ll*)malloc((N+1) * sizeof(ll));
    dp[0] = 0;
    
    // Deque for max H, using array
    int *deque = (int*)malloc((N+1) * sizeof(int));
    int dq_front = 0, dq_back = -1;
    
    ll sum_width = 0;
    int k = 1;
    for(int j=1; j<=N; j++){
        sum_width += W[j];
        
        // Maintain deque for max H
        while(dq_back >= dq_front && H[deque[dq_back]] <= H[j]){
            dq_back--;
        }
        dq_back++;
        deque[dq_back] = j;
        
        // Adjust k to maintain sum_width <= L
        while(sum_width > L){
            sum_width -= W[k];
            if(deque[dq_front] == k){
                dq_front++;
            }
            k++;
        }
        
        // Current max H is H[deque[dq_front]]
        ll current_max = H[deque[dq_front]];
        dp[j] = dp[k-1] + current_max;
    }
    
    printf("%lld\n", dp[N]);
    
    free(H);
    free(W);
    free(dp);
    free(deque);
    return 0;
}