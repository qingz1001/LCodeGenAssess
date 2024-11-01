#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

typedef long long ll;

typedef struct {
    ll sum;
    ll pre_max;
    ll suf_max;
    ll max_sum;
    int len;
    int pre_len;
    int suf_len;
    int max_len;
    ll lazy;
} Node;

int n, q;
Node tree[1600005];
ll a_input[400005];

ll max_ll(ll a, ll b) {
    return a > b ? a : b;
}

ll max3_ll(ll a, ll b, ll c) {
    return max_ll(max_ll(a, b), c);
}

void push_up(int idx) {
    int left = idx << 1;
    int right = left | 1;
    Node L = tree[left];
    Node R = tree[right];
    Node P;
    P.len = L.len + R.len;
    P.sum = L.sum + R.sum;
    
    if (L.pre_max > L.sum + R.pre_max) {
        P.pre_max = L.pre_max;
        P.pre_len = L.pre_len;
    }
    else {
        P.pre_max = L.sum + R.pre_max;
        P.pre_len = L.len + R.pre_len;
    }

    if (R.suf_max > R.sum + L.suf_max) {
        P.suf_max = R.suf_max;
        P.suf_len = R.suf_len;
    }
    else {
        P.suf_max = R.sum + L.suf_max;
        P.suf_len = R.len + L.suf_len;
    }

    if (L.max_sum > R.max_sum && L.max_sum > L.suf_max + R.pre_max) {
        P.max_sum = L.max_sum;
        P.max_len = L.max_len;
    }
    else if (R.max_sum > L.max_sum && R.max_sum > L.suf_max + R.pre_max) {
        P.max_sum = R.max_sum;
        P.max_len = R.max_len;
    }
    else {
        P.max_sum = L.suf_max + R.pre_max;
        P.max_len = L.suf_len + R.pre_len;
    }

    tree[idx] = P;
}

void apply(int idx, ll delta) {
    tree[idx].sum += delta * tree[idx].len;
    tree[idx].pre_max += delta * tree[idx].pre_len;
    tree[idx].suf_max += delta * tree[idx].suf_len;
    tree[idx].max_sum += delta * tree[idx].max_len;
    tree[idx].lazy += delta;
}

void push_down(int idx) {
    if (tree[idx].lazy != 0) {
        apply(idx<<1, tree[idx].lazy);
        apply((idx<<1)|1, tree[idx].lazy);
        tree[idx].lazy = 0;
    }
}

void build(int idx, int l, int r) {
    tree[idx].len = r - l + 1;
    tree[idx].lazy = 0;
    if (l == r) {
        ll val = a_input[l];
        tree[idx].sum = val;
        tree[idx].pre_max = val > 0 ? val : 0;
        tree[idx].pre_len = val > 0 ? 1 : 0;
        tree[idx].suf_max = val > 0 ? val : 0;
        tree[idx].suf_len = val > 0 ? 1 : 0;
        tree[idx].max_sum = val > 0 ? val : 0;
        tree[idx].max_len = val > 0 ? 1 : 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(idx<<1, l, mid);
    build((idx<<1)|1, mid+1, r);
    push_up(idx);
}

void range_add(int idx, int l, int r, int ql, int qr, ll delta) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        apply(idx, delta);
        return;
    }
    push_down(idx);
    int mid = (l + r) >> 1;
    range_add(idx<<1, l, mid, ql, qr, delta);
    range_add((idx<<1)|1, mid+1, r, ql, qr, delta);
    push_up(idx);
}

typedef struct {
    ll sum;
    ll pre_max;
    ll suf_max;
    ll max_sum;
    int len;
    int pre_len;
    int suf_len;
    int max_len;
} Res;

Res query_range(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        Res res;
        res.sum = 0;
        res.pre_max = res.suf_max = res.max_sum = 0;
        res.len = 0;
        res.pre_len = res.suf_len = res.max_len = 0;
        return res;
    }
    if (ql <= l && r <= qr) {
        Res res;
        res.sum = tree[idx].sum;
        res.pre_max = tree[idx].pre_max;
        res.suf_max = tree[idx].suf_max;
        res.max_sum = tree[idx].max_sum;
        res.len = tree[idx].len;
        res.pre_len = tree[idx].pre_len;
        res.suf_len = tree[idx].suf_len;
        res.max_len = tree[idx].max_len;
        return res;
    }
    push_down(idx);
    int mid = (l + r) >> 1;
    Res left = query_range(idx<<1, l, mid, ql, qr);
    Res right = query_range((idx<<1)|1, mid+1, r, ql, qr);
    if (left.len == 0) return right;
    if (right.len == 0) return left;
    Res res;
    res.sum = left.sum + right.sum;
    
    if (left.pre_max > left.sum + right.pre_max) {
        res.pre_max = left.pre_max;
        res.pre_len = left.pre_len;
    }
    else {
        res.pre_max = left.sum + right.pre_max;
        res.pre_len = left.len + right.pre_len;
    }

    if (right.suf_max > right.sum + left.suf_max) {
        res.suf_max = right.suf_max;
        res.suf_len = right.suf_len;
    }
    else {
        res.suf_max = right.sum + left.suf_max;
        res.suf_len = right.len + left.suf_len;
    }

    if (left.max_sum > right.max_sum && left.max_sum > left.suf_max + right.pre_max) {
        res.max_sum = left.max_sum;
        res.max_len = left.max_len;
    }
    else if (right.max_sum > left.max_sum && right.max_sum > left.suf_max + right.pre_max) {
        res.max_sum = right.max_sum;
        res.max_len = right.max_len;
    }
    else {
        res.max_sum = left.suf_max + right.pre_max;
        res.max_len = left.suf_len + right.pre_len;
    }

    return res;
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &a_input[i]);
    build(1,1,n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            range_add(1,1,n,l,r,x);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            Res res = query_range(1,1,n,l,r);
            ll answer = res.max_sum;
            answer = max_ll(answer, 0LL);
            printf("%lld\n", answer);
        }
    }
}