#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_Q 200005

typedef struct Node {
    int l, r;
    int min, max;
    long long sum;
} Node;

Node tree[MAX_N * 4];
int h[MAX_N], water[MAX_N];
int n, q;

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {
        tree[node].min = tree[node].max = h[l];
        tree[node].sum = h[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].min = (tree[node * 2].min < tree[node * 2 + 1].min) ? tree[node * 2].min : tree[node * 2 + 1].min;
    tree[node].max = (tree[node * 2].max > tree[node * 2 + 1].max) ? tree[node * 2].max : tree[node * 2 + 1].max;
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}

void update(int node, int pos, int val) {
    if (tree[node].l == tree[node].r) {
        tree[node].min = tree[node].max = val;
        tree[node].sum = val;
        return;
    }
    int mid = (tree[node].l + tree[node].r) / 2;
    if (pos <= mid) update(node * 2, pos, val);
    else update(node * 2 + 1, pos, val);
    tree[node].min = (tree[node * 2].min < tree[node * 2 + 1].min) ? tree[node * 2].min : tree[node * 2 + 1].min;
    tree[node].max = (tree[node * 2].max > tree[node * 2 + 1].max) ? tree[node * 2].max : tree[node * 2 + 1].max;
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
}

int query_min(int node, int l, int r) {
    if (l <= tree[node].l && tree[node].r <= r) return tree[node].min;
    int mid = (tree[node].l + tree[node].r) / 2;
    int res = 1e9;
    if (l <= mid) res = query_min(node * 2, l, r);
    if (r > mid) {
        int tmp = query_min(node * 2 + 1, l, r);
        res = (res < tmp) ? res : tmp;
    }
    return res;
}

long long query_sum(int node, int l, int r) {
    if (l <= tree[node].l && tree[node].r <= r) return tree[node].sum;
    int mid = (tree[node].l + tree[node].r) / 2;
    long long res = 0;
    if (l <= mid) res += query_sum(node * 2, l, r);
    if (r > mid) res += query_sum(node * 2 + 1, l, r);
    return res;
}

void pour_water(int x, int h) {
    int l = x, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (query_min(1, x, mid) < h) r = mid - 1;
        else l = mid;
    }
    long long sum = query_sum(1, x, l);
    long long total = (long long)(l - x + 1) * h;
    if (total > sum) {
        for (int i = x; i <= l; i++) {
            water[i] = h;
        }
    }
}

void drain_water(int x) {
    water[x] = 0;
}

void raise_wall(int x, int h) {
    if (h > tree[1].max) {
        update(1, x, h);
    }
}

int query_water(int x) {
    return water[x];
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &h[i]);
    }
    h[n - 1] = 1e9;  // Right wall is infinitely high
    
    build(1, 0, n - 1);
    
    for (int i = 0; i < q; i++) {
        int op, x, h;
        scanf("%d %d %d", &op, &x, &h);
        if (op == 0) {
            scanf("%d", &h);
            pour_water(x - 1, h);
        } else if (op == 1) {
            drain_water(x - 1);
        } else if (op == 2) {
            scanf("%d", &h);
            raise_wall(x - 1, h);
        } else if (op == 3) {
            printf("%d\n", query_water(x - 1));
        }
    }
    
    return 0;
}