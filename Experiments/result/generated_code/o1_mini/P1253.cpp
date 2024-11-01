#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAXN 1000005
#define MAXTREE (4*MAXN)

ll tree_max_val[MAXTREE];
ll tree_add_lazy[MAXTREE];
ll tree_set_lazy[MAXTREE];
int has_set_lazy[MAXTREE];
int n, q;
ll a[MAXN];

void build(int node, int l, int r){
    if(l == r){
        tree_max_val[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree_max_val[node] = tree_max_val[node*2] > tree_max_val[node*2+1] ? tree_max_val[node*2] : tree_max_val[node*2+1];
}

void pushdown(int node, int l, int r){
    if(has_set_lazy[node]){
        int mid = (l + r) / 2;
        int left = node*2, right = node*2+1;
        ll val = tree_set_lazy[node];
        tree_set_lazy[left] = val;
        tree_set_lazy[right] = val;
        has_set_lazy[left] = has_set_lazy[right] = 1;
        tree_add_lazy[left] = tree_add_lazy[right] = 0;
        tree_max_val[left] = val;
        tree_max_val[right] = val;
        has_set_lazy[node] = 0;
    }
    if(tree_add_lazy[node] != 0){
        int mid = (l + r) / 2;
        int left = node*2, right = node*2+1;
        ll add = tree_add_lazy[node];
        if(has_set_lazy[left]){
            tree_set_lazy[left] += add;
        }
        else{
            tree_add_lazy[left] += add;
        }
        tree_max_val[left] += add;
        if(has_set_lazy[right]){
            tree_set_lazy[right] += add;
        }
        else{
            tree_add_lazy[right] += add;
        }
        tree_max_val[right] += add;
        tree_add_lazy[node] = 0;
    }
}

void range_add(int node, int l, int r, int L, int R, ll val){
    if(R < l || L > r) return;
    if(L <= l && r <= R){
        if(has_set_lazy[node]){
            tree_set_lazy[node] += val;
        }
        else{
            tree_add_lazy[node] += val;
        }
        tree_max_val[node] += val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    range_add(node*2, l, mid, L, R, val);
    range_add(node*2+1, mid+1, r, L, R, val);
    tree_max_val[node] = tree_max_val[node*2] > tree_max_val[node*2+1] ? tree_max_val[node*2] : tree_max_val[node*2+1];
}

void range_set(int node, int l, int r, int L, int R, ll val){
    if(R < l || L > r) return;
    if(L <= l && r <= R){
        tree_set_lazy[node] = val;
        has_set_lazy[node] = 1;
        tree_add_lazy[node] = 0;
        tree_max_val[node] = val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    range_set(node*2, l, mid, L, R, val);
    range_set(node*2+1, mid+1, r, L, R, val);
    tree_max_val[node] = tree_max_val[node*2] > tree_max_val[node*2+1] ? tree_max_val[node*2] : tree_max_val[node*2+1];
}

ll range_query(int node, int l, int r, int L, int R){
    if(R < l || L > r) return -9223372036854775807LL;
    if(L <= l && r <= R){
        return tree_max_val[node];
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    ll res1 = range_query(node*2, l, mid, L, R);
    ll res2 = range_query(node*2+1, mid+1, r, L, R);
    return res1 > res2 ? res1 : res2;
}

int main(){
    // Fast IO
    ios:
    int i;
    scanf("%d %d", &n, &q);
    for(i=1;i<=n;i++) scanf("%lld", &a[i]);
    build(1,1,n);
    while(q--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            range_set(1,1,n,l,r,x);
        }
        else if(op == 2){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            range_add(1,1,n,l,r,x);
        }
        else if(op == 3){
            int l, r;
            scanf("%d %d", &l, &r);
            ll res = range_query(1,1,n,l,r);
            printf("%lld\n", res);
        }
    }
    return 0;
}