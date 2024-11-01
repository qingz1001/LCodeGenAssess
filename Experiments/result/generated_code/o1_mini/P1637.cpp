#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    // Coordinate compression
    int *sorted = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) sorted[i] = a[i];
    qsort(sorted, n, sizeof(int), cmp);
    int unique = 0;
    for(int i=0;i<n;i++) {
        if(i==0 || sorted[i]!=sorted[i-1]) sorted[unique++] = sorted[i];
    }
    
    // Function to get rank
    auto get_rank = [&](int x) -> int {
        int left = 0, right = unique-1, mid, res = unique;
        while(left <= right){
            mid = left + (right - left)/2;
            if(sorted[mid] >= x){
                res = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        return res +1;
    };
    
    // Initialize right_count
    int *right_count = (int*)malloc(n * sizeof(int));
    int size = unique +2;
    ll *BIT_right = (ll*)calloc(size, sizeof(ll));
    for(int i=n-1;i>=0;i--){
        int rank = get_rank(a[i]);
        right_count[i] = BIT_right[size-1] - BIT_right[rank];
        // Update BIT_right
        int idx = rank;
        while(idx < size){
            BIT_right[idx]++;
            idx += idx & -idx;
        }
    }
    
    // Initialize left_count and calculate result
    ll *BIT_left = (ll*)calloc(size, sizeof(ll));
    ll res = 0;
    for(int i=0;i<n;i++){
        int rank = get_rank(a[i]);
        ll cnt = BIT_left[rank-1];
        res += cnt * right_count[i];
        // Update BIT_left
        int idx = rank;
        while(idx < size){
            BIT_left[idx]++;
            idx += idx & -idx;
        }
    }
    
    printf("%lld\n", res);
    
    // Free memory
    free(a);
    free(sorted);
    free(right_count);
    free(BIT_right);
    free(BIT_left);
    
    return 0;
}