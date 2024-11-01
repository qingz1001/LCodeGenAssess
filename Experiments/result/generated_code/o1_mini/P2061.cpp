#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll maxh;
    ll minh;
    ll lazy;
} Node;

int cmp(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int binary_search_ll(ll *arr, int size, ll key) {
    int left = 0, right = size -1, mid;
    while(left <= right){
        mid = left + (right - left)/2;
        if(arr[mid] == key) return mid;
        if(arr[mid] < key) left = mid +1;
        else right = mid -1;
    }
    return left;
}

Node segtree[320000];
ll sorted_pos[80000];
int M;

void build(int node, int l, int r) {
    segtree[node].lazy = 0;
    if(l +1 == r){
        segtree[node].maxh = 0;
        segtree[node].minh = 0;
        return;
    }
    int mid = (l + r)/2;
    build(node*2, l, mid);
    build(node*2+1, mid, r);
    segtree[node].maxh = 0;
    segtree[node].minh = 0;
}

void push_down(int node, int l, int r){
    if(segtree[node].lazy != 0){
        int mid = (l + r)/2;
        ll h = segtree[node].lazy;
        // Left child
        if(segtree[node*2].maxh < h){
            segtree[node*2].maxh = h;
            segtree[node*2].minh = h;
            segtree[node*2].lazy = h;
        }
        else if(segtree[node*2].minh < h){
            segtree[node*2].lazy = h > segtree[node*2].lazy ? h : segtree[node*2].lazy;
        }
        // Right child
        if(segtree[node*2+1].maxh < h){
            segtree[node*2+1].maxh = h;
            segtree[node*2+1].minh = h;
            segtree[node*2+1].lazy = h;
        }
        else if(segtree[node*2+1].minh < h){
            segtree[node*2+1].lazy = h > segtree[node*2+1].lazy ? h : segtree[node*2+1].lazy;
        }
        segtree[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur, ll h){
    if(ur <= l || r <= ul) return;
    if(ul <= l && r <= ur){
        if(segtree[node].maxh < h){
            segtree[node].maxh = h;
            segtree[node].minh = h;
            segtree[node].lazy = h;
            return;
        }
        if(segtree[node].minh >= h){
            return;
        }
    }
    if(l +1 == r){
        if(segtree[node].maxh < h){
            segtree[node].maxh = h;
            segtree[node].minh = h;
        }
        return;
    }
    push_down(node, l, r);
    int mid = (l + r)/2;
    update_range(node*2, l, mid, ul, ur, h);
    update_range(node*2+1, mid, r, ul, ur, h);
    if(segtree[node*2].maxh > segtree[node*2+1].maxh){
        segtree[node].maxh = segtree[node*2].maxh;
    }
    else{
        segtree[node].maxh = segtree[node*2+1].maxh;
    }
    if(segtree[node*2].minh < segtree[node*2+1].minh){
        segtree[node].minh = segtree[node*2].minh;
    }
    else{
        segtree[node].minh = segtree[node*2+1].minh;
    }
}

ll total_sum = 0;

void compute_sum(int node, int l, int r, ll *positions){
    if(l +1 == r){
        total_sum += (positions[r] - positions[l]) * segtree[node].maxh;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r)/2;
    compute_sum(node*2, l, mid, positions);
    compute_sum(node*2+1, mid, r, positions);
}

int main(){
    int N;
    scanf("%d", &N);
    ll A[N], B[N], H[N];
    ll coords[2*N];
    for(int i=0;i<N;i++){
        scanf("%lld %lld %lld", &A[i], &B[i], &H[i]);
        coords[2*i] = A[i];
        coords[2*i+1] = B[i];
    }
    // Sort and deduplicate
    qsort(coords, 2*N, sizeof(ll), cmp);
    M = 0;
    sorted_pos[M++] = coords[0];
    for(int i=1;i<2*N;i++){
        if(coords[i] != sorted_pos[M-1]){
            sorted_pos[M++] = coords[i];
        }
    }
    build(1, 0, M-1);
    for(int i=0;i<N;i++){
        int a_idx = binary_search_ll(sorted_pos, M, A[i]);
        int b_idx = binary_search_ll(sorted_pos, M, B[i]);
        update_range(1, 0, M-1, a_idx, b_idx, H[i]);
    }
    compute_sum(1, 0, M-1, sorted_pos);
    printf("%lld\n", total_sum);
    return 0;
}