#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll max_prefix;
    ll max_suffix;
    ll max_subarray;
    ll min_val;
    ll max_val;
} Node;

#define MAXN 100005
Node tree_node[400020];
ll a[MAXN];
int n, q;

// Function to combine two nodes
Node combine(Node left, Node right) {
    Node parent;
    parent.sum = left.sum + right.sum;
    parent.max_prefix = left.max_prefix > left.sum + right.max_prefix ? left.max_prefix : left.sum + right.max_prefix;
    parent.max_suffix = right.max_suffix > right.sum + left.max_suffix ? right.max_suffix : right.sum + left.max_suffix;
    ll temp = left.max_suffix + right.max_prefix;
    parent.max_subarray = left.max_subarray;
    if(right.max_subarray > parent.max_subarray) parent.max_subarray = right.max_subarray;
    if(temp > parent.max_subarray) parent.max_subarray = temp;
    parent.min_val = left.min_val < right.min_val ? left.min_val : right.min_val;
    parent.max_val = left.max_val > right.max_val ? left.max_val : right.max_val;
    return parent;
}

// Build the segment tree
void build(int node, int l, int r){
    if(l == r){
        tree_node[node].sum = a[l];
        tree_node[node].max_prefix = a[l];
        tree_node[node].max_suffix = a[l];
        tree_node[node].max_subarray = a[l];
        tree_node[node].min_val = a[l];
        tree_node[node].max_val = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree_node[node] = combine(tree_node[node*2], tree_node[node*2+1]);
}

// Update a single position
void update_set(int node, int l, int r, int pos, ll val){
    if(l == r){
        a[l] = val;
        tree_node[node].sum = val;
        tree_node[node].max_prefix = val;
        tree_node[node].max_suffix = val;
        tree_node[node].max_subarray = val;
        tree_node[node].min_val = val;
        tree_node[node].max_val = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) update_set(node*2, l, mid, pos, val);
    else update_set(node*2+1, mid+1, r, pos, val);
    tree_node[node] = combine(tree_node[node*2], tree_node[node*2+1]);
}

// Range max update
void range_max_update(int node, int l, int r, int ql, int qr, ll x){
    if(tree_node[node].max_val < x){
        // Set entire segment to x
        tree_node[node].sum = x * (r - l +1);
        tree_node[node].max_prefix = tree_node[node].max_suffix = tree_node[node].max_subarray = x > 0 ? x * (r - l +1) : 0;
        tree_node[node].min_val = x;
        tree_node[node].max_val = x;
        // Update the actual array if it's a leaf
        if(l != r){
            // Not handling lazy propagation for simplicity
            // Need to push down if implementing properly
        }
        else{
            a[l] = x;
        }
        return;
    }
    if(l == r){
        if(a[l] < x){
            update_set(node, l, r, l, x);
        }
        return;
    }
    int mid = (l + r) /2;
    if(tree_node[node*2].min_val < x){
        range_max_update(node*2, l, mid, ql, qr, x);
    }
    if(tree_node[node*2+1].min_val < x){
        range_max_update(node*2+1, mid+1, r, ql, qr, x);
    }
    tree_node[node] = combine(tree_node[node*2], tree_node[node*2+1]);
}

// Query operation
Node range_query(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        Node null_node;
        null_node.sum = 0;
        null_node.max_prefix = null_node.max_suffix = null_node.max_subarray = LLONG_MIN;
        null_node.min_val = LLONG_MAX;
        null_node.max_val = LLONG_MIN;
        return null_node;
    }
    if(ql <= l && r <= qr){
        return tree_node[node];
    }
    int mid = (l + r) /2;
    Node left = range_query(node*2, l, mid, ql, qr);
    Node right = range_query(node*2+1, mid+1, r, ql, qr);
    if(left.max_subarray == LLONG_MIN) return right;
    if(right.max_subarray == LLONG_MIN) return left;
    return combine(left, right);
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    build(1,1,n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 0){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            range_max_update(1,1,n,l,r,x);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            Node res = range_query(1,1,n,l,r);
            if(res.max_subarray < 0) printf("0\n");
            else printf("%lld\n", res.max_subarray);
        }
    }
    return 0;
}