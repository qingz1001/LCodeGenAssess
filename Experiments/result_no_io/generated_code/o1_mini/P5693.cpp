#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll sum;
    ll pre;
    ll suf;
    ll mx;
    ll add;
} Node;

int n, q;
Node tree[1600000];
ll a_initial[400005];

void build(int node, int l, int r){
    tree[node].add = 0;
    if(l == r){
        ll val = a_initial[l];
        tree[node].sum = val;
        tree[node].pre = tree[node].suf = tree[node].mx = val > 0 ? val : 0;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node].sum = tree[node*2].sum + tree[node*2+1].sum;
    tree[node].pre = tree[node*2].pre > tree[node*2].sum + tree[node*2+1].pre ? tree[node*2].pre : tree[node*2].sum + tree[node*2+1].pre;
    tree[node].suf = tree[node*2+1].suf > tree[node*2+1].sum + tree[node*2].suf ? tree[node*2+1].suf : tree[node*2+1].sum + tree[node*2].suf;
    ll mx = tree[node*2].mx;
    if(tree[node*2+1].mx > mx) mx = tree[node*2+1].mx;
    ll cross = tree[node*2].suf + tree[node*2+1].pre;
    if(cross > mx) mx = cross;
    tree[node].mx = mx;
}

void pushdown(int node, int l, int r){
    if(tree[node].add != 0){
        int mid = (l + r) / 2;
        ll x = tree[node].add;
        // Left child
        tree[node*2].sum += x * (mid - l +1);
        tree[node*2].pre += x > 0 ? x * (mid - l +1) : 0;
        tree[node*2].suf += x > 0 ? x * (mid - l +1) : 0;
        tree[node*2].mx += x > 0 ? x * (mid - l +1) : 0;
        tree[node*2].add += x;
        // Right child
        tree[node*2+1].sum += x * (r - mid);
        tree[node*2+1].pre += x > 0 ? x * (r - mid) : 0;
        tree[node*2+1].suf += x > 0 ? x * (r - mid) : 0;
        tree[node*2+1].mx += x > 0 ? x * (r - mid) : 0;
        tree[node*2+1].add += x;
        tree[node].add = 0;
    }
}

void update_range(int node, int l, int r, int L, int R, ll x){
    if(R < l || L > r) return;
    if(L <= l && r <= R){
        tree[node].sum += x * (r - l +1);
        tree[node].pre += x > 0 ? x * (r - l +1) : 0;
        tree[node].suf += x > 0 ? x * (r - l +1) : 0;
        tree[node].mx += x > 0 ? x * (r - l +1) : 0;
        tree[node].add += x;
        return;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, L, R, x);
    update_range(node*2+1, mid+1, r, L, R, x);
    tree[node].sum = tree[node*2].sum + tree[node*2+1].sum;
    tree[node].pre = tree[node*2].pre > tree[node*2].sum + tree[node*2+1].pre ? tree[node*2].pre : tree[node*2].sum + tree[node*2+1].pre;
    tree[node].suf = tree[node*2+1].suf > tree[node*2+1].sum + tree[node*2].suf ? tree[node*2+1].suf : tree[node*2+1].sum + tree[node*2].suf;
    ll mx = tree[node*2].mx > tree[node*2+1].mx ? tree[node*2].mx : tree[node*2+1].mx;
    ll cross = tree[node*2].suf + tree[node*2+1].pre;
    if(cross > mx) mx = cross;
    tree[node].mx = mx;
}

struct NodeRes {
    ll sum;
    ll pre;
    ll suf;
    ll mx;
} res;

struct NodeRes query_range(int node, int l, int r, int L, int R){
    if(R < l || L > r){
        struct NodeRes tmp = {0, 0, 0, 0};
        return tmp;
    }
    if(L <= l && r <= R){
        struct NodeRes tmp;
        tmp.sum = tree[node].sum;
        tmp.pre = tree[node].pre;
        tmp.suf = tree[node].suf;
        tmp.mx = tree[node].mx;
        return tmp;
    }
    pushdown(node, l, r);
    int mid = (l + r) / 2;
    struct NodeRes left = query_range(node*2, l, mid, L, R);
    struct NodeRes right = query_range(node*2+1, mid+1, r, L, R);
    struct NodeRes ans;
    ans.sum = left.sum + right.sum;
    ans.pre = left.pre > left.sum + right.pre ? left.pre : left.sum + right.pre;
    ans.suf = right.suf > right.sum + left.suf ? right.suf : right.sum + left.suf;
    ans.mx = left.mx > right.mx ? left.mx : right.mx;
    ll cross = left.suf + right.pre;
    if(cross > ans.mx) ans.mx = cross;
    return ans;
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &a_initial[i]);
    build(1, 1, n);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            update_range(1, 1, n, l, r, x);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            struct NodeRes ans = query_range(1, 1, n, l, r);
            if(ans.mx < 0) ans.mx = 0;
            printf("%lld\n", ans.mx);
        }
    }
    return 0;
}