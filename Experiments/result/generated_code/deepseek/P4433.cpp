#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

void update(ll *tree, ll *lazy, ll node, ll start, ll end, ll l, ll r, ll A, ll B) {
    if (lazy[node] != 0) {
        tree[node] = mod(tree[node] + lazy[node] * (end - start + 1), MOD);
        if (start != end) {
            lazy[node * 2] = mod(lazy[node * 2] + lazy[node], MOD);
            lazy[node * 2 + 1] = mod(lazy[node * 2 + 1] + lazy[node], MOD);
        }
        lazy[node] = 0;
    }

    if (start > end || start > r || end < l) return;

    if (start >= l && end <= r) {
        tree[node] = mod(tree[node] + A * (end - start + 1), MOD);
        if (start != end) {
            lazy[node * 2] = mod(lazy[node * 2] + A, MOD);
            lazy[node * 2 + 1] = mod(lazy[node * 2 + 1] + A, MOD);
        }
        return;
    }

    ll mid = (start + end) / 2;
    update(tree, lazy, node * 2, start, mid, l, r, A, B);
    update(tree, lazy, node * 2 + 1, mid + 1, end, l, r, A, B);
    tree[node] = mod(tree[node * 2] + tree[node * 2 + 1], MOD);
}

ll query(ll *tree, ll *lazy, ll node, ll start, ll end, ll l, ll r) {
    if (start > end || start > r || end < l) return 0;

    if (lazy[node] != 0) {
        tree[node] = mod(tree[node] + lazy[node] * (end - start + 1), MOD);
        if (start != end) {
            lazy[node * 2] = mod(lazy[node * 2] + lazy[node], MOD);
            lazy[node * 2 + 1] = mod(lazy[node * 2 + 1] + lazy[node], MOD);
        }
        lazy[node] = 0;
    }

    if (start >= l && end <= r) return tree[node];

    ll mid = (start + end) / 2;
    ll p1 = query(tree, lazy, node * 2, start, mid, l, r);
    ll p2 = query(tree, lazy, node * 2 + 1, mid + 1, end, l, r);
    return mod(p1 + p2, MOD);
}

int main() {
    ll n, q;
    scanf("%lld %lld", &n, &q);

    ll *tree = (ll *)calloc(4 * n, sizeof(ll));
    ll *lazy = (ll *)calloc(4 * n, sizeof(ll));

    for (ll i = 0; i < q; i++) {
        ll type, L, R, A, B;
        scanf("%lld %lld %lld", &type, &L, &R);
        if (type == 1) {
            scanf("%lld %lld", &A, &B);
            update(tree, lazy, 1, 1, n, L, R, A, B);
        } else if (type == 2) {
            printf("%lld\n", query(tree, lazy, 1, 1, n, L, R));
        }
    }

    free(tree);
    free(lazy);
    return 0;
}