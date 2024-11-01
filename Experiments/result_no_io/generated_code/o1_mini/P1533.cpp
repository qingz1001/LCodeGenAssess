#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int left;
    int right;
    int cnt;
} Node;

long long a[300005];
long long sorted_a[300005];
int roots[300005];
Node nodes[24000000];
int node_cnt = 0;

int cmp_func(const void *a_ptr, const void *b_ptr) {
    long long a_val = *(long long*)a_ptr;
    long long b_val = *(long long*)b_ptr;
    if(a_val < b_val) return -1;
    else if(a_val > b_val) return 1;
    else return 0;
}

int build(int l, int r){
    int p = node_cnt++;
    nodes[p].cnt = 0;
    if(l != r){
        int mid = (l + r) / 2;
        nodes[p].left = build(l, mid);
        nodes[p].right = build(mid+1, r);
    }
    else{
        nodes[p].left = nodes[p].right = -1;
    }
    return p;
}

int update_tree(int prev, int l, int r, int pos){
    int p = node_cnt++;
    nodes[p].cnt = nodes[prev].cnt +1;
    if(l != r){
        int mid = (l + r) / 2;
        if(pos <= mid){
            nodes[p].left = update_tree(nodes[prev].left, l, mid, pos);
            nodes[p].right = nodes[prev].right;
        }
        else{
            nodes[p].left = nodes[prev].left;
            nodes[p].right = update_tree(nodes[prev].right, mid+1, r, pos);
        }
    }
    else{
        nodes[p].left = nodes[p].right = -1;
    }
    return p;
}

int query_tree(int u, int v, int l, int r, int k){
    if(l == r){
        return l;
    }
    int mid = (l + r) / 2;
    int cnt = nodes[nodes[v].left].cnt - nodes[nodes[u].left].cnt;
    if(k <= cnt){
        return query_tree(nodes[u].left, nodes[v].left, l, mid, k);
    }
    else{
        return query_tree(nodes[u].right, nodes[v].right, mid+1, r, k - cnt);
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        scanf("%lld", &a[i]);
        sorted_a[i] = a[i];
    }
    qsort(sorted_a+1, n, sizeof(long long), cmp_func);
    // Assign compressed values
    // Since a[i] are unique
    // No need to remove duplicates
    // Function to get index
    #define GET_IDX(x) ( (int)( ( (x) == sorted_a[1] ) ? 1 : \
        ( ( (x) > sorted_a[n] ) ? n +1 : \
        ({ int l=1, r=n, res=n; while(l<=r){int mid=(l+r)/2; if(sorted_a[mid]>=x){res=mid; r=mid-1;} else {l=mid+1;}} res; }) ) ))
    // Initialize persistent segment tree
    int base = build(1, n);
    roots[0] = base;
    for(int i=1;i<=n;i++) {
        // Find the position of a[i] in sorted_a
        int pos;
        int l =1, r =n, res = n;
        while(l <= r){
            int mid = (l + r)/2;
            if(sorted_a[mid] >= a[i]){
                res = mid;
                r = mid -1;
            }
            else{
                l = mid +1;
            }
        }
        pos = res;
        roots[i] = update_tree(roots[i-1], 1, n, pos);
    }
    for(int q_num=0; q_num<m; q_num++){
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        int res_pos = query_tree(roots[i-1], roots[j], 1, n, k);
        printf("%lld\n", sorted_a[res_pos]);
    }
    return 0;
}