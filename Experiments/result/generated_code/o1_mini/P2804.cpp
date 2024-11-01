#include <stdio.h>
#include <stdlib.h>

#define MOD 92084931

typedef long long ll;

int cmp_ll(const void* a, const void* b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int lower_bound_ll(ll* sorted, int size, ll val){
    int left = 0, right = size;
    while(left < right){
        int mid = left + (right - left)/2;
        if(sorted[mid] < val){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

int main(){
    int n;
    ll M;
    scanf("%d %lld", &n, &M);
    ll* a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    ll* prefix = (ll*)malloc((n+1) * sizeof(ll));
    prefix[0] = 0;
    for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + (a[i-1] - M);
    ll* sorted = (ll*)malloc((n+1) * sizeof(ll));
    for(int i=0;i<=n;i++) sorted[i] = prefix[i];
    qsort(sorted, n+1, sizeof(ll), cmp_ll);
    int unique_size = 0;
    for(int i=0;i<=n;i++){
        if(i==0 || sorted[i] != sorted[i-1]) sorted[unique_size++] = sorted[i];
    }
    // BIT
    int size = unique_size;
    int* BITree = (int*)calloc(size+2, sizeof(int));
    ll count =0;
    // Update and Query functions
    auto update = [&](int idx) {
        while(idx <= size){
            BITree[idx] +=1;
            idx += idx & -idx;
        }
    };
    auto query = [&](int idx) -> int {
        int res =0;
        while(idx >0){
            res += BITree[idx];
            idx -= idx & -idx;
        }
        return res;
    };
    for(int i=0;i<=n;i++){
        int pos = lower_bound_ll(sorted, unique_size, prefix[i]);
        count = (count + query(pos)) % MOD;
        update(pos +1);
    }
    printf("%lld\n", count);
    free(a);
    free(prefix);
    free(sorted);
    free(BITree);
    return 0;
}