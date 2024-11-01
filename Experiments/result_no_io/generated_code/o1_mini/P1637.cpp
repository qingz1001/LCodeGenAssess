#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int n;
    scanf("%d", &n);
    int* a = (int*)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    // Coordinate compression
    int* sorted = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) sorted[i] = a[i+1];
    qsort(sorted, n, sizeof(int), cmp);
    int m = 1;
    for(int i=1;i<n;i++) if(sorted[i]!=sorted[m-1]) sorted[m++] = sorted[i];
    // Function to get compressed value
    auto get_idx = [&](int x) -> int{
        int left=0, right=m-1, mid, res=m;
        while(left <= right){
            mid = left + (right - left)/2;
            if(sorted[mid] >= x){
                res = mid+1;
                right = mid-1;
            }
            else left = mid+1;
        }
        return res;
    };
    
    // Left counts
    ll* left_counts = (ll*)calloc(n+1, sizeof(ll));
    ll* right_counts = (ll*)calloc(n+1, sizeof(ll));
    ll* BIT1 = (ll*)calloc(m+2, sizeof(ll));
    // BIT functions
    auto update = [&](ll* BIT, int idx) {
        while(idx <= m){
            BIT[idx]++;
            idx += idx & -idx;
        }
    };
    auto query = [&](ll* BIT, int idx) -> ll{
        ll res = 0;
        while(idx > 0){
            res += BIT[idx];
            idx -= idx & -idx;
        }
        return res;
    };
    // Calculate left_counts
    for(int i=1;i<=n;i++){
        int idx = get_idx(a[i]);
        left_counts[i] = query(BIT1, idx -1);
        update(BIT1, idx);
    }
    // Calculate right_counts
    ll* BIT2 = (ll*)calloc(m+2, sizeof(ll));
    for(int i=n;i>=1;i--){
        int idx = get_idx(a[i]);
        right_counts[i] = query(BIT2, m) - query(BIT2, idx);
        update(BIT2, idx);
    }
    // Calculate total
    ll total = 0;
    for(int i=1;i<=n;i++) total += left_counts[i] * right_counts[i];
    printf("%lld\n", total);
    free(a);
    free(sorted);
    free(left_counts);
    free(right_counts);
    free(BIT1);
    free(BIT2);
    return 0;
}