#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INF 100000000000000LL

typedef long long ll;

// Function to compare two ll values for qsort
int cmp_ll(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

// Function to find the first index >= target in X[start..end]
int lower_bound_func(ll X[], int start, int end, ll target) {
    int l = start;
    int r = end;
    int res = end +1;
    while(l <= r){
        int mid = l + (r - l)/2;
        if(X[mid] >= target){
            res = mid;
            r = mid -1;
        }
        else{
            l = mid +1;
        }
    }
    if(res > end) return end+1;
    return res;
}

// Function to find the last index <= target in X[start..end]
int upper_bound_func(ll X[], int start, int end, ll target) {
    int l = start;
    int r = end;
    int res = start -1;
    while(l <= r){
        int mid = l + (r - l)/2;
        if(X[mid] <= target){
            res = mid;
            l = mid +1;
        }
        else{
            r = mid -1;
        }
    }
    if(res < start) return start -1;
    return res;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    
    ll *D = (ll*)malloc((N-1)*sizeof(ll));
    for(int i=0;i<N-1;i++) scanf("%lld", &D[i]);
    
    ll *C = (ll*)malloc(N*sizeof(ll));
    for(int i=0;i<N;i++) scanf("%lld", &C[i]);
    
    ll *S = (ll*)malloc(N*sizeof(ll));
    for(int i=0;i<N;i++) scanf("%lld", &S[i]);
    
    ll *W = (ll*)malloc(N*sizeof(ll));
    for(int i=0;i<N;i++) scanf("%lld", &W[i]);
    
    // Compute X[1..N]
    ll *X = (ll*)malloc((N+1)*sizeof(ll));
    X[1] = 0;
    for(int i=2;i<=N;i++) X[i] = D[i-2];
    
    // Compute prefix_w and suffix_w
    ll *prefix_w = (ll*)malloc((N+2)*sizeof(ll));
    prefix_w[0] = 0;
    for(int i=1;i<=N;i++) prefix_w[i] = prefix_w[i-1] + W[i-1];
    ll *suffix_w = (ll*)malloc((N+2)*sizeof(ll));
    for(int i=0;i<=N;i++) suffix_w[i] = prefix_w[N] - prefix_w[i];
    
    // Compute l[j] and r[j]
    int *l = (int*)malloc((N+1)*sizeof(int));
    int *r = (int*)malloc((N+1)*sizeof(int));
    for(int j=1;j<=N;j++){
        ll target_l = X[j] - S[j-1];
        int lb = lower_bound_func(X, 1, j, target_l);
        if(lb > j) lb = j;
        l[j] = lb;
        
        ll target_r = X[j] + S[j-1];
        int ub = upper_bound_func(X, j, N, target_r);
        if(ub < j) ub = j;
        r[j] = ub;
    }
    
    // Initialize dp arrays
    ll *prev_dp = (ll*)malloc((N+1)*sizeof(ll));
    ll *current_dp = (ll*)malloc((N+1)*sizeof(ll));
    for(int i=0;i<=N;i++) prev_dp[i] = prefix_w[i];
    
    // Initialize min_cost with dp[0][N]
    ll min_cost = prev_dp[N];
    
    for(int k=1; k<=K; k++){
        for(int i=0;i<=N;i++) current_dp[i] = INF;
        for(int j=1; j<=N; j++){
            int lj = l[j];
            int rj = r[j];
            if(lj-1 >=0 && rj <=N){
                ll temp = prev_dp[lj-1] + C[j-1] + suffix_w[rj];
                if(temp < current_dp[rj]){
                    current_dp[rj] = temp;
                }
            }
        }
        // Propagate the minimum to the right
        for(int i=1;i<=N;i++){
            if(current_dp[i] > current_dp[i-1]){
                current_dp[i] = current_dp[i-1];
            }
        }
        // Update min_cost
        if(current_dp[N] < min_cost){
            min_cost = current_dp[N];
        }
        // Swap prev_dp and current_dp
        ll *temp_ptr = prev_dp;
        prev_dp = current_dp;
        current_dp = temp_ptr;
    }
    
    printf("%lld\n", min_cost);
    
    // Free memory
    free(D);
    free(C);
    free(S);
    free(W);
    free(X);
    free(prefix_w);
    free(suffix_w);
    free(l);
    free(r);
    free(prev_dp);
    free(current_dp);
    
    return 0;
}