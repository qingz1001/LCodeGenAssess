#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 200005
#define MAXQ 100005

long long tree[MAXN * 4];
long long lazy[MAXN * 4];
int n, q;

void push_down(int node, int l, int r) {
    if (lazy[node]) {
        tree[node] += (r - l + 1) * lazy[node];
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &tree[node]);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int node, int l, int r, int ul, int ur, int val) {
    push_down(node, l, r);
    if (ul <= l && r <= ur) {
        lazy[node] += val;
        push_down(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if (ul <= mid) update(node * 2, l, mid, ul, ur, val);
    if (ur > mid) update(node * 2 + 1, mid + 1, r, ul, ur, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query_sum(int node, int l, int r, int ql, int qr) {
    push_down(node, l, r);
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) res += query_sum(node * 2, l, mid, ql, qr);
    if (qr > mid) res += query_sum(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

long long query_min(int node, int l, int r, int ql, int qr) {
    push_down(node, l, r);
    if (ql <= l && r <= qr) return tree[node] / (r - l + 1);
    int mid = (l + r) / 2;
    long long res = LLONG_MAX;
    if (ql <= mid) res = query_min(node * 2, l, mid, ql, qr);
    if (qr > mid) res = (res < query_min(node * 2 + 1, mid + 1, r, ql, qr)) ? res : query_min(node * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    
    char op;
    int a, b, c;
    for (int i = 0; i < q; i++) {
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &a, &b);
            printf("%lld\n", query_min(1, 1, n, a, b));
        } else if (op == 'P') {
            scanf("%d %d %d", &a, &b, &c);
            update(1, 1, n, a, b, c);
        } else if (op == 'S') {
            scanf("%d %d", &a, &b);
            printf("%lld\n", query_sum(1, 1, n, a, b));
        }
    }
    
    return 0;
}