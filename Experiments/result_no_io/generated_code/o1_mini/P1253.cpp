#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll maxv;
    ll add;
    ll set;
    int has_set;
} Node;

Node *tree;
int n;

void build(int idx, int l, int r, ll a[]) {
    if (l == r) {
        tree[idx].maxv = a[l];
        tree[idx].add = 0;
        tree[idx].set = 0;
        tree[idx].has_set = 0;
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid, a);
    build(idx*2+1, mid+1, r, a);
    tree[idx].maxv = tree[idx*2].maxv > tree[idx*2+1].maxv ? tree[idx*2].maxv : tree[idx*2+1].maxv;
    tree[idx].add = 0;
    tree[idx].set = 0;
    tree[idx].has_set = 0;
}

void push_down(int idx, int l, int r) {
    if (tree[idx].has_set) {
        int mid = (l + r) / 2;
        int left = idx*2, right = idx*2+1;
        tree[left].has_set = tree[right].has_set = 1;
        tree[left].set = tree[right].set = tree[idx].set;
        tree[left].add = tree[right].add = 0;
        tree[left].maxv = tree[idx].set;
        tree[right].maxv = tree[idx].set;
        tree[idx].has_set = 0;
    }
    if (tree[idx].add != 0) {
        int mid = (l + r) / 2;
        int left = idx*2, right = idx*2+1;
        if (tree[left].has_set) {
            tree[left].set += tree[idx].add;
            tree[left].maxv += tree[idx].add;
        }
        else {
            tree[left].add += tree[idx].add;
            tree[left].maxv += tree[idx].add;
        }
        if (tree[right].has_set) {
            tree[right].set += tree[idx].add;
            tree[right].maxv += tree[idx].add;
        }
        else {
            tree[right].add += tree[idx].add;
            tree[right].maxv += tree[idx].add;
        }
        tree[idx].add = 0;
    }
}

void update_set(int idx, int l, int r, int L, int R, ll val) {
    if (L > r || R < l) return;
    if (L <= l && r <= R) {
        tree[idx].has_set = 1;
        tree[idx].set = val;
        tree[idx].add = 0;
        tree[idx].maxv = val;
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    update_set(idx*2, l, mid, L, R, val);
    update_set(idx*2+1, mid+1, r, L, R, val);
    tree[idx].maxv = tree[idx*2].maxv > tree[idx*2+1].maxv ? tree[idx*2].maxv : tree[idx*2+1].maxv;
}

void update_add(int idx, int l, int r, int L, int R, ll val) {
    if (L > r || R < l) return;
    if (L <= l && r <= R) {
        if (tree[idx].has_set) {
            tree[idx].set += val;
            tree[idx].maxv += val;
        }
        else {
            tree[idx].add += val;
            tree[idx].maxv += val;
        }
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    update_add(idx*2, l, mid, L, R, val);
    update_add(idx*2+1, mid+1, r, L, R, val);
    tree[idx].maxv = tree[idx*2].maxv > tree[idx*2+1].maxv ? tree[idx*2].maxv : tree[idx*2+1].maxv;
}

ll query_max(int idx, int l, int r, int L, int R) {
    if (L > r || R < l) return -(__INT64_MAX__);
    if (L <= l && r <= R) {
        return tree[idx].maxv;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    ll res1 = query_max(idx*2, l, mid, L, R);
    ll res2 = query_max(idx*2+1, mid+1, r, L, R);
    return res1 > res2 ? res1 : res2;
}

int main(){
    int q;
    scanf("%d %d", &n, &q);
    ll *a = (ll*)malloc((n+1)*sizeof(ll));
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    tree = (Node*)malloc((4*n+4)*sizeof(Node));
    memset(tree, 0, (4*n+4)*sizeof(Node));
    build(1, 1, n, a);
    while(q--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            update_set(1, 1, n, l, r, x);
        }
        else if(op == 2){
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            update_add(1, 1, n, l, r, x);
        }
        else if(op == 3){
            int l, r;
            scanf("%d %d", &l, &r);
            ll res = query_max(1, 1, n, l, r);
            printf("%lld\n", res);
        }
    }
    free(a);
    free(tree);
    return 0;
}