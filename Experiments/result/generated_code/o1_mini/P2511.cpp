#include <stdio.h>
#include <stdlib.h>

#define MOD 10007
#define MAX_N 50001
#define MAX_M 1001

long long prefix_sum[MAX_N];
int L[MAX_N];
int n, m;

// Function to check if a given max_sum is possible with at most m cuts
int is_possible(long long max_sum) {
    int cuts = 0;
    long long current = 0;
    for(int i = 1; i <= n; i++) {
        if(L[i] > max_sum) return 0;
        if(current + L[i] > max_sum) {
            cuts++;
            current = L[i];
            if(cuts > m) return 0;
        }
        else {
            current += L[i];
        }
    }
    return 1;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        scanf("%d", &L[i]);
    }

    // Binary search to find minimal possible maximum segment sum
    long long low = L[1];
    long long high = 0;
    for(int i=1;i<=n;i++) {
        if(L[i] > low) low = L[i];
        high += L[i];
    }

    long long S = high;
    while(low <= high){
        long long mid = low + (high - low)/2;
        if(is_possible(mid)){
            S = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }

    // Now count the number of ways to partition with maximum segment sum <= S
    // Using DP with prefix sums
    // dp[k] represents number of ways with k cuts up to current position
    // To optimize, use prefix arrays for each k
    // Due to memory constraints, use separate prefix arrays for each k

    // Initialize prefix_sum for k=0
    long long *dp_prev = (long long*)calloc(m+1, sizeof(long long));
    long long *prefix_prev = (long long*)calloc(m+1, sizeof(long long));
    dp_prev[0] = 1;
    prefix_prev[0] = 1;
    for(int k=1; k<=m; k++) {
        prefix_prev[k] = 0;
    }

    for(int i=1; i<=n; i++) {
        // Find the earliest j where sum[j+1..i] <= S
        // Using prefix_sum array
        // Compute prefix_sum[i] = prefix_sum[i-1] + L[i]
        prefix_sum[i] = prefix_sum[i-1] + L[i];
        int j = 1;
        while(j <= i && prefix_sum[i] - prefix_sum[j-1] > S){
            j++;
        }
        // Now, j-1 is the last position where prefix_sum[j-1..i] <= S
        // For each k, update the number of ways
        long long *dp_new = (long long*)calloc(m+1, sizeof(long long));
        long long *prefix_new = (long long*)calloc(m+1, sizeof(long long));
        for(int k=0; k<=m; k++) {
            if(k ==0){
                if(prefix_sum[i] <= S){
                    dp_new[k] =1;
                }
                else{
                    dp_new[k] =0;
                }
            }
            else{
                if(j-1 >=0){
                    dp_new[k] = (prefix_prev[k-1] - (j-1 >0 ? prefix_prev[k-1] : 0)) % MOD;
                    if(dp_new[k] <0) dp_new[k] += MOD;
                }
                else{
                    dp_new[k] =0;
                }
            }
            prefix_new[k] = (i ==1 ? dp_new[k] : (prefix_prev[k] + dp_new[k])%MOD);
            if(i >1){
                prefix_new[k] = (prefix_prev[k] + dp_new[k])%MOD;
            }
            else{
                prefix_new[k] = dp_new[k];
            }
        }
        // Update dp_prev and prefix_prev
        for(int k=0; k<=m; k++) {
            dp_prev[k] = dp_new[k];
            prefix_prev[k] = (i ==1 ? dp_new[k] : (prefix_prev[k] + dp_new[k])%MOD);
        }
        free(dp_new);
        free(prefix_new);
    }

    // Now, sum up all dp_prev[k] for k from0 to m
    long long total =0;
    for(int k=0; k<=m; k++) {
        total = (total + dp_prev[k]) % MOD;
    }

    printf("%lld %lld\n", S, total);

    free(dp_prev);
    free(prefix_prev);
    return 0;
}