#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005
#define MAXS 6000000

long long a[MAXN];
long long sorted_a[MAXN];
int version_roots[MAXN];
int left_child[MAXS];
int right_child[MAXS];
int cnt_tree[MAXS];
int total_nodes = 0;

// Comparator for qsort
int cmp(const void *a_ptr, const void *b_ptr) {
    long long a_val = *((long long*)a_ptr);
    long long b_val = *((long long*)b_ptr);
    if (a_val < b_val)
        return -1;
    else if (a_val > b_val)
        return 1;
    else
        return 0;
}

// Insert function for persistent segment tree
int insert(int prev, int l, int r, int x) {
    int now = total_nodes++;
    cnt_tree[now] = cnt_tree[prev] + 1;
    if (l == r) {
        left_child[now] = right_child[now] = 0;
        return now;
    }
    int m = (l + r) / 2;
    if (x <= m) {
        left_child[now] = insert(left_child[prev], l, m, x);
        right_child[now] = right_child[prev];
    }
    else {
        left_child[now] = left_child[prev];
        right_child[now] = insert(right_child[prev], m+1, r, x);
    }
    return now;
}

// Query function for persistent segment tree
int query_kth(int u, int v, int l, int r, int k) {
    if (l == r)
        return l;
    int m = (l + r) / 2;
    int cnt = cnt_tree[left_child[v]] - cnt_tree[left_child[u]];
    if (cnt >= k)
        return query_kth(left_child[u], left_child[v], l, m, k);
    else
        return query_kth(right_child[u], right_child[v], m+1, r, k - cnt);
}

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2) return 0;
    for(int i=1;i<=n;i++) {
        if(scanf("%lld", &a[i])!=1) return 0;
        sorted_a[i] = a[i];
    }
    qsort(sorted_a+1, n, sizeof(long long), cmp);
    // Build versions
    version_roots[0] = 0;
    for(int i=1;i<=n;i++) {
        // Binary search to find the rank
        int low=1, high=n, pos=1;
        while(low <= high){
            int mid = (low + high)/2;
            if(sorted_a[mid] == a[i]){
                pos = mid;
                break;
            }
            else if(sorted_a[mid] < a[i]){
                low = mid +1;
            }
            else{
                high = mid -1;
            }
        }
        version_roots[i] = insert(version_roots[i-1], 1, n, pos);
    }
    // Process queries
    for(int i=0;i<m;i++) {
        int l, r, k;
        if(scanf("%d %d %d", &l, &r, &k)!=3) return 0;
        int res = query_kth(version_roots[l-1], version_roots[r], 1, n, k);
        printf("%lld\n", sorted_a[res]);
    }
    return 0;
}