#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 1000000
ll tree_min_node[4000005];
ll tree_lazy_node[4000005];
ll r_vals[1000005];
int n, m;

// Build the segment tree
void build(int node, int l, int r) {
    if (l == r) {
        tree_min_node[node] = r_vals[l];
        tree_lazy_node[node] = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree_min_node[node] = tree_min_node[2*node] < tree_min_node[2*node+1] ? tree_min_node[2*node] : tree_min_node[2*node+1];
    tree_lazy_node[node] = 0;
}

// Push down the lazy value
void push_down(int node, int l, int r) {
    if (tree_lazy_node[node] != 0) {
        int mid = (l + r) / 2;
        ll val = tree_lazy_node[node];
        tree_min_node[2*node] -= val;
        tree_min_node[2*node+1] -= val;
        tree_lazy_node[2*node] += val;
        tree_lazy_node[2*node+1] += val;
        tree_lazy_node[node] = 0;
    }
}

// Range minimum query
ll range_min(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 1e18;
    if (ql <= l && r <= qr) return tree_min_node[node];
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll res1 = range_min(2*node, l, mid, ql, qr);
    ll res2 = range_min(2*node+1, mid+1, r, ql, qr);
    return res1 < res2 ? res1 : res2;
}

// Range update: subtract val
void range_update(int node, int l, int r, int ql, int qr, ll val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree_min_node[node] -= val;
        tree_lazy_node[node] += val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    range_update(2*node, l, mid, ql, qr, val);
    range_update(2*node+1, mid+1, r, ql, qr, val);
    tree_min_node[node] = tree_min_node[2*node] < tree_min_node[2*node+1] ? tree_min_node[2*node] : tree_min_node[2*node+1];
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%lld", &r_vals[i]);
    build(1,1,n);
    for(int j=1; j<=m; j++){
        ll d, s, t;
        scanf("%lld %lld %lld", &d, &s, &t);
        ll current_min = range_min(1,1,n, s, t);
        if(current_min >= d){
            range_update(1,1,n, s, t, d);
        }
        else{
            printf("-1\n%d\n", j);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}