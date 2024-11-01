#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MOD 571373

typedef long long ll;

typedef struct {
    ll sum, add, mul;
} Node;

Node tree[4 * MAXN];
ll arr[MAXN];

void push_up(int node) {
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
}

void push_down(int node, int start, int end) {
    int mid = (start + end) / 2;
    tree[node * 2].sum = (tree[node * 2].sum * tree[node].mul + tree[node].add * (mid - start + 1)) % MOD;
    tree[node * 2 + 1].sum = (tree[node * 2 + 1].sum * tree[node].mul + tree[node].add * (end - mid)) % MOD;

    tree[node * 2].mul = (tree[node * 2].mul * tree[node].mul) % MOD;
    tree[node * 2 + 1].mul = (tree[node * 2 + 1].mul * tree[node].mul) % MOD;

    tree[node * 2].add = (tree[node * 2].add * tree[node].mul + tree[node].add) % MOD;
    tree[node * 2 + 1].add = (tree[node * 2 + 1].add * tree[node].mul + tree[node].add) % MOD;

    tree[node].add = 0;
    tree[node].mul = 1;
}

void build(int node, int start, int end) {
    tree[node].add = 0;
    tree[node].mul = 1;
    if (start == end) {
        tree[node].sum = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        push_up(node);
    }
}

void update_add(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].sum = (tree[node].sum + val * (end - start + 1)) % MOD;
        tree[node].add = (tree[node].add + val) % MOD;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update_add(node * 2, start, mid, l, r, val);
    if (r > mid) update_add(node * 2 + 1, mid + 1, end, l, r, val);
    push_up(node);
}

void update_mul(int node, int start, int end, int l, int r, ll val) {
    if (l <= start && end <= r) {
        tree[node].sum = (tree[node].sum * val) % MOD;
        tree[node].mul = (tree[node].mul * val) % MOD;
        tree[node].add = (tree[node].add * val) % MOD;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update_mul(node * 2, start, mid, l, r, val);
    if (r > mid) update_mul(node * 2 + 1, mid + 1, end, l, r, val);
    push_up(node);
}

ll query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].sum;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    ll sum = 0;
    if (l <= mid) sum = (sum + query(node * 2, start, mid, l, r)) % MOD;
    if (r > mid) sum = (sum + query(node * 2 + 1, mid + 1, end, l, r)) % MOD;
    return sum;
}

int main() {
    int n, q, m;
    scanf("%d %d %d", &n, &q, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    build(1, 1, n);
    while (q--) {
        int op, x, y;
        ll k;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            scanf("%lld", &k);
            update_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            scanf("%lld", &k);
            update_add(1, 1, n, x, y, k);
        } else if (op == 3) {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}