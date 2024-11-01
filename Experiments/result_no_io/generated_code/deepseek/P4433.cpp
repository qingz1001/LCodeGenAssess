#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

void update(ll *tree, ll *lazy_a, ll *lazy_b, ll node, ll start, ll end, ll l, ll r, ll a, ll b) {
    if (lazy_a[node] != 0 || lazy_b[node] != 0) {
        ll len = end - start + 1;
        tree[node] = mod(tree[node] + (lazy_a[node] * (start + end) * len / 2) % b + (lazy_b[node] * len) % b, b);
        if (start != end) {
            lazy_a[node * 2] = mod(lazy_a[node * 2] + lazy_a[node], b);
            lazy_b[node * 2] = mod(lazy_b[node * 2] + lazy_b[node], b);
            lazy_a[node * 2 + 1] = mod(lazy_a[node * 2 + 1] + lazy_a[node], b);
            lazy_b[node * 2 + 1] = mod(lazy_b[node * 2 + 1] + lazy_b[node], b);
        }
        lazy_a[node] = 0;
        lazy_b[node] = 0;
    }

    if (start > end || start > r || end < l) return;

    if (start >= l && end <= r) {
        ll len = end - start + 1;
        tree[node] = mod(tree[node] + (a * (start + end) * len / 2) % b + (b * len) % b, b);
        if (start != end) {
            lazy_a[node * 2] = mod(lazy_a[node * 2] + a, b);
            lazy_b[node * 2] = mod(lazy_b[node * 2] + b, b);
            lazy_a[node * 2 + 1] = mod(lazy_a[node * 2 + 1] + a, b);
            lazy_b[node * 2 + 1] = mod(lazy_b[node * 2 + 1] + b, b);
        }
        return;
    }

    ll mid = (start + end) / 2;
    update(tree, lazy_a, lazy_b, node * 2, start, mid, l, r, a, b);
    update(tree, lazy_a, lazy_b, node * 2 + 1, mid + 1, end, l, r, a, b);
    tree[node] = mod(tree[node * 2] + tree[node * 2 + 1], b);
}

ll query(ll *tree, ll *lazy_a, ll *lazy_b, ll node, ll start, ll end, ll l, ll r, ll b) {
    if (start > end || start > r || end < l) return 0;

    if (lazy_a[node] != 0 || lazy_b[node] != 0) {
        ll len = end - start + 1;
        tree[node] = mod(tree[node] + (lazy_a[node] * (start + end) * len / 2) % b + (lazy_b[node] * len) % b, b);
        if (start != end) {
            lazy_a[node * 2] = mod(lazy_a[node * 2] + lazy_a[node], b);
            lazy_b[node * 2] = mod(lazy_b[node * 2] + lazy_b[node], b);
            lazy_a[node * 2 + 1] = mod(lazy_a[node * 2 + 1] + lazy_a[node], b);
            lazy_b[node * 2 + 1] = mod(lazy_b[node * 2 + 1] + lazy_b[node], b);
        }
        lazy_a[node] = 0;
        lazy_b[node] = 0;
    }

    if (start >= l && end <= r) return tree[node];

    ll mid = (start + end) / 2;
    ll p1 = query(tree, lazy_a, lazy_b, node * 2, start, mid, l, r, b);
    ll p2 = query(tree, lazy_a, lazy_b, node * 2 + 1, mid + 1, end, l, r, b);
    return mod(p1 + p2, b);
}

int main() {
    ll n, q;
    scanf("%lld %lld", &n, &q);

    ll *tree = (ll *)calloc(4 * n, sizeof(ll));
    ll *lazy_a = (ll *)calloc(4 * n, sizeof(ll));
    ll *lazy_b = (ll *)calloc(4 * n, sizeof(ll));

    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            ll l, r, a, b;
            scanf("%lld %lld %lld %lld", &l, &r, &a, &b);
            update(tree, lazy_a, lazy_b, 1, 1, n, l, r, a, b);
        } else if (type == 2) {
            ll l, r;
            scanf("%lld %lld", &l, &r);
            printf("%lld\n", query(tree, lazy_a, lazy_b, 1, 1, n, l, r, MOD));
        }
    }

    free(tree);
    free(lazy_a);
    free(lazy_b);

    return 0;
}