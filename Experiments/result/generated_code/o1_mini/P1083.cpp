#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    ll min;
    ll lazy;
} Node;

Node* tree;
int n;

ll build_tree(int idx, int l, int r, ll* arr){
    if(l == r){
        tree[idx].min = arr[l];
        tree[idx].lazy = 0;
        return tree[idx].min;
    }
    int mid = (l + r) / 2;
    ll left = build_tree(2*idx, l, mid, arr);
    ll right = build_tree(2*idx+1, mid+1, r, arr);
    tree[idx].min = left < right ? left : right;
    tree[idx].lazy = 0;
    return tree[idx].min;
}

void push_down(int idx, int l, int r){
    if(tree[idx].lazy != 0){
        int mid = (l + r) / 2;
        tree[2*idx].min -= tree[idx].lazy;
        tree[2*idx+1].min -= tree[idx].lazy;
        tree[2*idx].lazy += tree[idx].lazy;
        tree[2*idx+1].lazy += tree[idx].lazy;
        tree[idx].lazy = 0;
    }
}

ll range_min(int idx, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return LLONG_MAX;
    }
    if(ql <= l && r <= qr){
        return tree[idx].min;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    ll res1 = range_min(2*idx, l, mid, ql, qr);
    ll res2 = range_min(2*idx+1, mid+1, r, ql, qr);
    return res1 < res2 ? res1 : res2;
}

void range_subtract(int idx, int l, int r, int ql, int qr, ll val){
    if(ql > r || qr < l){
        return;
    }
    if(ql <= l && r <= qr){
        tree[idx].min -= val;
        tree[idx].lazy += val;
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    range_subtract(2*idx, l, mid, ql, qr, val);
    range_subtract(2*idx+1, mid+1, r, ql, qr, val);
    tree[idx].min = tree[2*idx].min < tree[2*idx+1].min ? tree[2*idx].min : tree[2*idx+1].min;
}

int main(){
    int m;
    scanf("%d %d", &n, &m);
    ll* arr = (ll*)malloc((n+1)*sizeof(ll));
    for(int i=1;i<=n;i++) scanf("%lld", &arr[i]);
    int size = 1;
    while(size < n) size <<=1;
    tree = (Node*)malloc((size*2+2)*sizeof(Node));
    build_tree(1,1,n, arr);
    free(arr);
    int failed = 0;
    int fail_id = 0;
    for(int j=1; j<=m; j++){
        ll d, s, t;
        scanf("%lld %lld %lld", &d, &s, &t);
        ll current_min = range_min(1,1,n,s,t);
        if(current_min < d){
            failed = 1;
            fail_id = j;
            break;
        }
        range_subtract(1,1,n,s,t,d);
    }
    if(failed){
        printf("-1\n%d\n", fail_id);
    }
    else{
        printf("0\n");
    }
    free(tree);
    return 0;
}