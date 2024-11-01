#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll max_prefix;
    ll max_suffix;
    ll max_subarray;
    ll min_val;
    ll max_val;
    ll assign;
    int has_assign;
} Node;

int n, q;
ll a_initial[100005];
Node tree[400020];

ll max_ll(ll a, ll b) {
    return a > b ? a : b;
}

ll min_ll(ll a, ll b) {
    return a < b ? a : b;
}

void combine(Node *parent, Node *left, Node *right) {
    parent->sum = left->sum + right->sum;
    parent->max_prefix = max_ll(left->max_prefix, left->sum + right->max_prefix);
    parent->max_suffix = max_ll(right->max_suffix, right->sum + left->max_suffix);
    parent->max_subarray = max_ll(max_ll(left->max_subarray, right->max_subarray), left->max_suffix + right->max_prefix);
    parent->min_val = min_ll(left->min_val, right->min_val);
    parent->max_val = max_ll(left->max_val, right->max_val);
}

void apply_assign(Node *node, int l, int r, ll val) {
    node->sum = val * (r - l + 1);
    node->max_prefix = node->max_suffix = node->max_subarray = max_ll(val, node->sum);
    node->min_val = node->max_val = val;
    node->assign = val;
    node->has_assign = 1;
}

void push_down(int idx, int l, int r) {
    if (tree[idx].has_assign) {
        int mid = (l + r) / 2;
        apply_assign(&tree[idx*2], l, mid, tree[idx].assign);
        apply_assign(&tree[idx*2+1], mid+1, r, tree[idx].assign);
        tree[idx].has_assign = 0;
    }
}

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx].sum = a_initial[l];
        tree[idx].max_prefix = tree[idx].max_suffix = tree[idx].max_subarray = a_initial[l];
        tree[idx].min_val = tree[idx].max_val = a_initial[l];
        tree[idx].has_assign = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    combine(&tree[idx], &tree[idx*2], &tree[idx*2+1]);
    tree[idx].has_assign = 0;
}

void update_max_util(int idx, int l, int r, int ql, int qr, ll x) {
    if (qr < l || ql > r) return;
    if (ql <= l && r <= qr) {
        if (tree[idx].min_val >= x) return;
        if (tree[idx].max_val < x) {
            apply_assign(&tree[idx], l, r, x);
            return;
        }
    }
    if (l == r) {
        if (tree[idx].sum < x) {
            tree[idx].sum = x;
            tree[idx].max_prefix = tree[idx].max_suffix = tree[idx].max_subarray = x;
            tree[idx].min_val = tree[idx].max_val = x;
        }
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    update_max_util(idx*2, l, mid, ql, qr, x);
    update_max_util(idx*2+1, mid+1, r, ql, qr, x);
    combine(&tree[idx], &tree[idx*2], &tree[idx*2+1]);
}

typedef struct {
    ll sum;
    ll max_prefix;
    ll max_suffix;
    ll max_subarray;
    ll min_val;
    ll max_val;
} Res;

Res query_util(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) {
        Res empty;
        empty.sum = 0;
        empty.max_prefix = empty.max_suffix = empty.max_subarray = LLONG_MIN;
        empty.min_val = LLONG_MAX;
        empty.max_val = LLONG_MIN;
        return empty;
    }
    if (ql <= l && r <= qr) {
        Res res;
        res.sum = tree[idx].sum;
        res.max_prefix = tree[idx].max_prefix;
        res.max_suffix = tree[idx].max_suffix;
        res.max_subarray = tree[idx].max_subarray;
        res.min_val = tree[idx].min_val;
        res.max_val = tree[idx].max_val;
        return res;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    Res left = query_util(idx*2, l, mid, ql, qr);
    Res right = query_util(idx*2+1, mid+1, r, ql, qr);
    if (left.max_subarray == LLONG_MIN) return right;
    if (right.max_subarray == LLONG_MIN) return left;
    Res res;
    res.sum = left.sum + right.sum;
    res.max_prefix = max_ll(left.max_prefix, left.sum + right.max_prefix);
    res.max_suffix = max_ll(right.max_suffix, right.sum + left.max_suffix);
    res.max_subarray = max_ll(max_ll(left.max_subarray, right.max_subarray), left.max_suffix + right.max_prefix);
    res.min_val = min_ll(left.min_val, right.min_val);
    res.max_val = max_ll(left.max_val, right.max_val);
    return res;
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &a_initial[i]);
    build(1, 1, n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 0){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            update_max_util(1, 1, n, l, r, x);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            Res ans = query_util(1, 1, n, l, r);
            if(ans.max_subarray < 0) printf("0\n");
            else printf("%lld\n", ans.max_subarray);
        }
    }
}