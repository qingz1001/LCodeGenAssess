#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll lazy;
} Node;

Node tree_nodes[400005];
ll arr[100005];
int n, m;

void build(int node, int l, int r){
    if(l == r){
        tree_nodes[node].sum = arr[l];
        tree_nodes[node].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree_nodes[node].sum = tree_nodes[node*2].sum + tree_nodes[node*2+1].sum;
    tree_nodes[node].lazy = 0;
}

void pushdown(int node, int l, int r){
    if(tree_nodes[node].lazy != 0){
        int mid = (l + r) / 2;
        ll val = tree_nodes[node].lazy;
        tree_nodes[node*2].sum += val * (mid - l +1);
        tree_nodes[node*2+1].sum += val * (r - mid);
        tree_nodes[node*2].lazy += val;
        tree_nodes[node*2+1].lazy += val;
        tree_nodes[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur, ll val){
    if(ul > r || ur < l){
        return;
    }
    if(ul <= l && r <= ur){
        tree_nodes[node].sum += val * (r - l +1);
        tree_nodes[node].lazy += val;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ul, ur, val);
    update_range(node*2+1, mid+1, r, ul, ur, val);
    tree_nodes[node].sum = tree_nodes[node*2].sum + tree_nodes[node*2+1].sum;
}

ll query_sum(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return 0;
    }
    if(ql <= l && r <= qr){
        return tree_nodes[node].sum;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(node*2, l, mid, ql, qr) + query_sum(node*2+1, mid+1, r, ql, qr);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &arr[i]);
    build(1, 1, n);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            update_range(1, 1, n, x, y, k);
        }
        else if(type == 2){
            int x, y;
            scanf("%d %d", &x, &y);
            ll res = query_sum(1, 1, n, x, y);
            printf("%lld\n", res);
        }
    }
    return 0;
}