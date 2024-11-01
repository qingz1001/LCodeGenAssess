#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll gcd_func(ll a, ll b) {
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

typedef struct {
    ll sum_v;
    ll sum_vk;
    ll sum_vk2;
    ll sum_k;
    ll sum_k2;
    ll lazy;
} Node;

Node tree[400005];
int n, m;

// Precompute sum of k and k^2 for each node
ll k_vals[100005];
ll k2_vals[100005];

void build(int node, int l, int r){
    tree[node].lazy = 0;
    if(l == r){
        tree[node].sum_v = 0;
        tree[node].sum_vk = 0;
        tree[node].sum_vk2 = 0;
        tree[node].sum_k = l;
        tree[node].sum_k2 = (ll)l * l;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node].sum_v = tree[node*2].sum_v + tree[node*2+1].sum_v;
    tree[node].sum_vk = tree[node*2].sum_vk + tree[node*2+1].sum_vk;
    tree[node].sum_vk2 = tree[node*2].sum_vk2 + tree[node*2+1].sum_vk2;
    tree[node].sum_k = tree[node*2].sum_k + tree[node*2+1].sum_k;
    tree[node].sum_k2 = tree[node*2].sum_k2 + tree[node*2+1].sum_k2;
}

void pushdown(int node, int l, int r){
    if(tree[node].lazy != 0){
        ll delta = tree[node].lazy;
        int mid = (l + r) / 2;
        int left = node*2;
        int right = node*2+1;
        // Update left child
        tree[left].sum_v += delta * (mid - l +1);
        tree[left].sum_vk += delta * tree[left].sum_k;
        tree[left].sum_vk2 += delta * tree[left].sum_k2;
        tree[left].lazy += delta;
        // Update right child
        tree[right].sum_v += delta * (r - mid);
        tree[right].sum_vk += delta * tree[right].sum_k;
        tree[right].sum_vk2 += delta * tree[right].sum_k2;
        tree[right].lazy += delta;
        // Clear lazy
        tree[node].lazy = 0;
    }
}

void update_range(int node, int l, int r, int ul, int ur, ll delta){
    if(ul > r || ur < l){
        return;
    }
    if(ul <= l && r <= ur){
        tree[node].sum_v += delta * (r - l +1);
        tree[node].sum_vk += delta * tree[node].sum_k;
        tree[node].sum_vk2 += delta * tree[node].sum_k2;
        tree[node].lazy += delta;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ul, ur, delta);
    update_range(node*2+1, mid+1, r, ul, ur, delta);
    tree[node].sum_v = tree[node*2].sum_v + tree[node*2+1].sum_v;
    tree[node].sum_vk = tree[node*2].sum_vk + tree[node*2+1].sum_vk;
    tree[node].sum_vk2 = tree[node*2].sum_vk2 + tree[node*2+1].sum_vk2;
}

typedef struct {
    ll sum_v;
    ll sum_vk;
    ll sum_vk2;
} Result;

Result query_range(int node, int l, int r, int ql, int qr){
    Result res = {0, 0, 0};
    if(ql > r || qr < l){
        return res;
    }
    if(ql <= l && r <= qr){
        res.sum_v = tree[node].sum_v;
        res.sum_vk = tree[node].sum_vk;
        res.sum_vk2 = tree[node].sum_vk2;
        return res;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    Result left = query_range(node*2, l, mid, ql, qr);
    Result right = query_range(node*2+1, mid+1, r, ql, qr);
    res.sum_v = left.sum_v + right.sum_v;
    res.sum_vk = left.sum_vk + right.sum_vk;
    res.sum_vk2 = left.sum_vk2 + right.sum_vk2;
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    build(1,1,n);
    char op;
    int l, r;
    ll v;
    while(m--){
        scanf(" %c", &op);
        if(op == 'C'){
            scanf("%d %d %lld", &l, &r, &v);
            if(l <= r-1)
                update_range(1, 1, n, l, r-1, v);
        }
        else{
            scanf("%d %d", &l, &r);
            if(l == r){
                printf("0/1\n");
                continue;
            }
            Result q = query_range(1, 1, n, l, r-1);
            ll sum_v = q.sum_v;
            ll sum_vk = q.sum_vk;
            ll sum_vk2 = q.sum_vk2;
            ll total = (l + r) * sum_vk - sum_vk2 - l * r * sum_v + r * sum_v;
            int len = r - l +1;
            ll numerator = 2 * total;
            ll denominator = (ll)len * (len -1);
            if(numerator == 0){
                printf("0/1\n");
                continue;
            }
            ll g = gcd_func(numerator <0 ? -numerator : numerator, denominator);
            numerator /= g;
            denominator /= g;
            printf("%lld/%lld\n", numerator, denominator);
        }
    }
    return 0;
}