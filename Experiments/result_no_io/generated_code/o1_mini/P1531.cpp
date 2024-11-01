#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

long long scores[MAXN];
long long tree[4 * MAXN];
int n, m;

// Build the segment tree
void build(int node, int l, int r){
    if(l == r){
        tree[node] = scores[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node] = tree[node*2] > tree[node*2+1] ? tree[node*2] : tree[node*2+1];
}

// Query the maximum in range [ql, qr]
long long query_max(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return -__LONG_LONG_MAX__;
    }
    if(ql <= l && r <= qr){
        return tree[node];
    }
    int mid = (l + r) / 2;
    long long left = query_max(node*2, l, mid, ql, qr);
    long long right = query_max(node*2+1, mid+1, r, ql, qr);
    return left > right ? left : right;
}

// Update the value at position pos to val if val > current
void update_val(int node, int l, int r, int pos, long long val){
    if(l == r){
        if(val > tree[node]){
            tree[node] = val;
        }
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid){
        update_val(node*2, l, mid, pos, val);
    }
    else{
        update_val(node*2+1, mid+1, r, pos, val);
    }
    tree[node] = tree[node*2] > tree[node*2+1] ? tree[node*2] : tree[node*2+1];
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &scores[i]);
    build(1, 1, n);
    char op;
    int a;
    long long b;
    for(int i=0;i<m;i++){
        scanf(" %c %d %lld", &op, &a, &b);
        if(op == 'Q'){
            long long res = query_max(1, 1, n, a, (int)b);
            printf("%lld\n", res);
        }
        else if(op == 'U'){
            if(scores[a] < b){
                scores[a] = b;
                update_val(1, 1, n, a, b);
            }
        }
    }
    return 0;
}