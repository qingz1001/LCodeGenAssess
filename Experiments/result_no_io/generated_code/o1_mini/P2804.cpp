#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

struct PrefixSum {
    ll val;
};

int cmp(const void *a, const void *b){
    ll A = ((struct PrefixSum*)a)->val;
    ll B = ((struct PrefixSum*)b)->val;
    if(A < B) return -1;
    if(A > B) return 1;
    return 0;
}

int main(){
    int n;
    ll M;
    scanf("%d %lld", &n, &M);
    ll *a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    struct PrefixSum *ps = (struct PrefixSum*)malloc((n+1) * sizeof(struct PrefixSum));
    ps[0].val = 0;
    for(int i=1;i<=n;i++) ps[i].val = ps[i-1].val + a[i-1] - M;
    qsort(ps, n+1, sizeof(struct PrefixSum), cmp);
    int *rank_arr = (int*)malloc((n+1) * sizeof(int));
    int unique = 0;
    for(int i=0;i<n+1;i++){
        if(i==0 || ps[i].val != ps[i-1].val){
            unique++;
        }
        rank_arr[i] = unique;
    }
    // Restore the original order
    struct PrefixSum *original = (struct PrefixSum*)malloc((n+1) * sizeof(struct PrefixSum));
    for(int i=0;i<n+1;i++) original[i].val = ps[i].val;
    qsort(ps, n+1, sizeof(struct PrefixSum), cmp);
    // BIT
    int size = unique + 2;
    int *BIT_tree = (int*)calloc(size, sizeof(int));
    auto lowbit = [](int x) -> int { return x & (-x); };
    void update_bit(int index){
        while(index < size){
            BIT_tree[index]++;
            index += lowbit(index);
        }
    }
    int query_bit(int index){
        int res = 0;
        while(index > 0){
            res += BIT_tree[index];
            index -= lowbit(index);
        }
        return res;
    }
    // Reconstruct ranks
    qsort(original, n+1, sizeof(struct PrefixSum), cmp);
    for(int i=0;i<n+1;i++) {
        ps[i].val = original[i].val;
    }
    // Reset and count
    free(ps);
    free(original);
    qsort(ps, n+1, sizeof(struct PrefixSum), cmp);
    // Now assign ranks
    qsort(ps, n+1, sizeof(struct PrefixSum), cmp);
    // Not needed anymore
    // Implement proper rank assignment
    // Start counting
    ll MOD = 92084931;
    ll res = 0;
    // Recompute ranks using sorted unique
    qsort(ps, n+1, sizeof(struct PrefixSum), cmp);
    int *sorted = (int*)malloc((n+1) * sizeof(int));
    for(int i=0;i<n+1;i++) sorted[i] = ps[i].val;
    // Assign rank
    // Not efficient, but for the purpose of the problem
    // Implement mapping
    ll *prefix = (ll*)malloc((n+1) * sizeof(ll));
    prefix[0] = 0;
    for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + a[i-1] - M;
    // Collect all prefix
    struct PrefixSum *all_ps = (struct PrefixSum*)malloc((n+1) * sizeof(struct PrefixSum));
    for(int i=0;i<=n;i++) all_ps[i].val = prefix[i];
    qsort(all_ps, n+1, sizeof(struct PrefixSum), cmp);
    int *ranks = (int*)malloc((n+1) * sizeof(int));
    int current = 1;
    ranks[0] = current;
    for(int i=1;i<n+1;i++){
        if(all_ps[i].val != all_ps[i-1].val){
            current++;
        }
        ranks[i] = current;
    }
    // Assign rank to each prefix
    for(int i=0;i<=n;i++){
        // Binary search
        int left = 0, right = n;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(all_ps[mid].val < prefix[i]) left = mid +1;
            else if(all_ps[mid].val > prefix[i]) right = mid -1;
            else {ranks[i] = ranks[mid]; break;}
        }
    }
    // Now count
    for(int i=0;i<=n;i++){
        // Number of prefix[j] < prefix[i]
        // which is query(ranks[i]-1)
        if(i >0){
            res = (res + query_bit(ranks[i]-1)) % MOD;
        }
        update_bit(ranks[i]);
    }
    printf("%lld", res);
    free(a);
    free(ps);
    free(rank_arr);
    free(BIT_tree);
    free(sorted);
    free(prefix);
    free(all_ps);
    free(ranks);
    return 0;
}