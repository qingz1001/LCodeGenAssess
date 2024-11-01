#include <stdio.h>
#include <string.h>
#define MAXN 100005
#define ll long long

ll n, p, m;
ll a[MAXN];

struct Node {
    ll sum, add, mul;
} tree[MAXN * 4];

void build(int node, int start, int end) {
    tree[node].mul = 1;
    if (start == end) {
        tree[node].sum = a[start] % p;
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % p;
}

void pushdown(int node, int start, int end) {
    int mid = (start + end) / 2;
    ll lnum = mid - start + 1, rnum = end - mid;
    
    tree[node * 2].sum = (tree[node * 2].sum * tree[node].mul + tree[node].add * lnum) % p;
    tree[node * 2 + 1].sum = (tree[node * 2 + 1].sum * tree[node].mul + tree[node].add * rnum) % p;
    
    tree[node * 2].mul = (tree[node * 2].mul * tree[node].mul) % p;
    tree[node * 2 + 1].mul = (tree[node * 2 + 1].mul * tree[node].mul) % p;
    
    tree[node * 2].add = (tree[node * 2].add * tree[node].mul + tree[node].add) % p;
    tree[node * 2 + 1].add = (tree[node * 2 + 1].add * tree[node].mul + tree[node].add) % p;
    
    tree[node].mul = 1;
    tree[node].add = 0;
}

void update_mul(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].sum = (tree[node].sum * val) % p;
        tree[node].mul = (tree[node].mul * val) % p;
        tree[node].add = (tree[node].add * val) % p;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update_mul(node * 2, start, mid, l, r, val);
    if (r > mid) update_mul(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % p;
}

void update_add(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].sum = (tree[node].sum + val * (end - start + 1)) % p;
        tree[node].add = (tree[node].add + val) % p;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update_add(node * 2, start, mid, l, r, val);
    if (r > mid) update_add(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % p;
}

ll query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].sum;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    ll res = 0;
    if (l <= mid) res = (res + query(node * 2, start, mid, l, r)) % p;
    if (r > mid) res = (res + query(node * 2 + 1, mid + 1, end, l, r)) % p;
    return res;
}

int main() {
    scanf("%lld %lld", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    scanf("%lld", &m);
    while (m--) {
        int op, t, g;
        ll c;
        scanf("%d %d %d", &op, &t, &g);
        if (op == 1) {
            scanf("%lld", &c);
            update_mul(1, 1, n, t, g, c);
        } else if (op == 2) {
            scanf("%lld", &c);
            update_add(1, 1, n, t, g, c);
        } else {
            printf("%lld\n", query(1, 1, n, t, g));
        }
    }
    return 0;
}