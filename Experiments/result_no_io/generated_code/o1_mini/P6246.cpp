#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXN 500005

typedef long long ll;

ll a[MAXN];
ll S[MAXN];
ll dp_prev[MAXN];
ll dp_curr[MAXN];
int n, m;

// Comparator for qsort
int cmp(const void *a_, const void *b_) {
    ll a_val = *(ll*)a_;
    ll b_val = *(ll*)b_;
    if (a_val < b_val) return -1;
    if (a_val > b_val) return 1;
    return 0;
}

// Function to compute cost(j+1, i)
ll cost(int j, int i) {
    if(j > i) return 0;
    int m_idx = (j + i) / 2;
    ll median = a[m_idx];
    ll left = median * (m_idx - j + 1) - (S[m_idx] - S[j-1]);
    ll right = (S[i] - S[m_idx]) - median * (i - m_idx);
    return left + right;
}

// Divide and Conquer DP
void compute(int k, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l + r) / 2;
    int best = optl;
    ll best_cost = cost(optl, mid) + dp_prev[optl];
    for(int j = optl + 1; j <= optr && j <= mid; j++) {
        ll current = cost(j, mid) + dp_prev[j];
        if(current < best_cost){
            best_cost = current;
            best = j;
        }
    }
    dp_curr[mid] = best_cost;
    compute(k, l, mid -1, optl, best);
    compute(k, mid +1, r, best, optr);
}

int main(){
    // Read input
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    
    // Sort the villages
    qsort(a+1, n, sizeof(ll), cmp);
    
    // Compute prefix sums
    S[0] = 0;
    for(int i=1;i<=n;i++) S[i] = S[i-1] + a[i];
    
    // Initialize dp_prev for k=1
    for(int i=1;i<=n;i++) {
        dp_prev[i] = cost(1, i);
    }
    
    // Iterate over each post office
    for(int k=2; k<=m; k++){
        // If k > i, set dp_curr[i] = 0
        int limit = n;
        if(k > n) limit = n;
        compute(k, k, limit, k-1, n-1);
        // Swap dp_prev and dp_curr
        for(int i=k; i<=n;i++) dp_prev[i] = dp_curr[i];
    }
    
    // If m >=n, answer is 0
    if(m >=n){
        printf("0\n");
        return 0;
    }
    
    printf("%lld\n", dp_prev[n]);
}