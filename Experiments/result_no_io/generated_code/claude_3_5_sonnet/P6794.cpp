#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_Q 200005

typedef long long ll;

typedef struct {
    int l, r;
    ll min, max, add;
} Node;

Node tree[MAX_N * 4];
int n, q;
ll h[MAX_N], water[MAX_N];

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    tree[node].min = tree[node].max = tree[node].add = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void push_down(int node) {
    if (tree[node].add) {
        tree[node * 2].min += tree[node].add;
        tree[node * 2].max += tree[node].add;
        tree[node * 2].add += tree[node].add;
        tree[node * 2 + 1].min += tree[node].add;
        tree[node * 2 + 1].max += tree[node].add;
        tree[node * 2 + 1].add += tree[node].add;
        tree[node].add = 0;
    }
}

void update(int node, int l, int r, ll val) {
    if (tree[node].l >= l && tree[node].r <= r) {
        tree[node].min += val;
        tree[node].max += val;
        tree[node].add += val;
        return;
    }
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    if (l <= mid) update(node * 2, l, r, val);
    if (r > mid) update(node * 2 + 1, l, r, val);
    tree[node].min = (tree[node * 2].min < tree[node * 2 + 1].min) ? tree[node * 2].min : tree[node * 2 + 1].min;
    tree[node].max = (tree[node * 2].max > tree[node * 2 + 1].max) ? tree[node * 2].max : tree[node * 2 + 1].max;
}

ll query(int node, int pos) {
    if (tree[node].l == tree[node].r) return tree[node].min;
    push_down(node);
    int mid = (tree[node].l + tree[node].r) / 2;
    if (pos <= mid) return query(node * 2, pos);
    else return query(node * 2 + 1, pos);
}

void pour_water(int x, ll height) {
    ll current = query(1, x);
    if (current >= height) return;
    update(1, x, x, height - current);
    int l = x - 1, r = x + 1;
    while (l >= 1 || r <= n) {
        if (l >= 1 && h[l] < height) {
            ll lh = query(1, l);
            if (lh < height) {
                update(1, l, l, height - lh);
                l--;
            } else break;
        }
        if (r <= n && h[r - 1] < height) {
            ll rh = query(1, r);
            if (rh < height) {
                update(1, r, r, height - rh);
                r++;
            } else break;
        }
        if ((l < 1 || h[l] >= height) && (r > n || h[r - 1] >= height)) break;
    }
}

void drain_water(int x) {
    ll height = query(1, x);
    update(1, x, x, -height);
}

void raise_wall(int x, ll new_height) {
    if (new_height <= h[x]) return;
    h[x] = new_height;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%lld", &h[i]);
    }
    build(1, 1, n);

    for (int i = 1; i <= q; i++) {
        int op, x;
        ll height;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%*d %d %lld", &x, &height);
            pour_water(x, height);
        } else if (op == 1) {
            scanf("%*d %d", &x);
            drain_water(x);
        } else if (op == 2) {
            scanf("%*d %d %lld", &x, &height);
            raise_wall(x, height);
        } else if (op == 3) {
            scanf("%*d %d", &x);
            printf("%lld\n", query(1, x));
        }
    }

    return 0;
}