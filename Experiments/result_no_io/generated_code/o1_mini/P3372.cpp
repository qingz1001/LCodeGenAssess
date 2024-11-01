#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll add;
} Node;

int n, m;
ll A[100005];
Node tree[400020];

void build(int idx, int l, int r){
    tree[idx].add = 0;
    if(l == r){
        tree[idx].sum = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    tree[idx].sum = tree[idx*2].sum + tree[idx*2+1].sum;
}

void pushdown(int idx, int l, int r){
    if(tree[idx].add != 0){
        int mid = (l + r) / 2;
        ll add_val = tree[idx].add;
        tree[idx*2].sum += add_val * (mid - l +1);
        tree[idx*2+1].sum += add_val * (r - mid);
        tree[idx*2].add += add_val;
        tree[idx*2+1].add += add_val;
        tree[idx].add = 0;
    }
}

void update_range(int idx, int l, int r, int ul, int ur, ll val){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        tree[idx].sum += val * (r - l +1);
        tree[idx].add += val;
        return;
    }
    pushdown(idx, l, r);
    int mid = (l + r) / 2;
    update_range(idx*2, l, mid, ul, ur, val);
    update_range(idx*2+1, mid+1, r, ul, ur, val);
    tree[idx].sum = tree[idx*2].sum + tree[idx*2+1].sum;
}

ll query_sum(int idx, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr){
        return tree[idx].sum;
    }
    pushdown(idx, l, r);
    int mid = (l + r) / 2;
    return query_sum(idx*2, l, mid, ql, qr) + query_sum(idx*2+1, mid+1, r, ql, qr);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &A[i]);
    build(1,1,n);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            update_range(1,1,n, x, y, k);
        }
        else{
            int x, y;
            scanf("%d %d", &x, &y);
            ll res = query_sum(1,1,n, x, y);
            printf("%lld\n", res);
        }
    }
    return 0;
}