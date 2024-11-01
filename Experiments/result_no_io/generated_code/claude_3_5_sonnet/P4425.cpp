#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define INF 0x3f3f3f3f

int n, m, p;
int T[MAX_N];
int next[MAX_N], prev[MAX_N];
int appear[MAX_N], disappear[MAX_N];

struct Node {
    int l, r, min;
} tree[MAX_N * 4];

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {
        tree[node].min = T[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].min = tree[node * 2].min < tree[node * 2 + 1].min ? tree[node * 2].min : tree[node * 2 + 1].min;
}

void update(int node, int pos, int val) {
    if (tree[node].l == tree[node].r) {
        tree[node].min = val;
        return;
    }
    int mid = (tree[node].l + tree[node].r) / 2;
    if (pos <= mid) update(node * 2, pos, val);
    else update(node * 2 + 1, pos, val);
    tree[node].min = tree[node * 2].min < tree[node * 2 + 1].min ? tree[node * 2].min : tree[node * 2 + 1].min;
}

int query(int node, int l, int r) {
    if (l <= tree[node].l && tree[node].r <= r) return tree[node].min;
    int mid = (tree[node].l + tree[node].r) / 2;
    int res = INF;
    if (l <= mid) {
        int tmp = query(node * 2, l, r);
        res = tmp < res ? tmp : res;
    }
    if (r > mid) {
        int tmp = query(node * 2 + 1, l, r);
        res = tmp < res ? tmp : res;
    }
    return res;
}

int solve() {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        appear[i] = query(1, i, i);
        disappear[i] = query(1, next[i], i);
        if (disappear[i] < appear[i]) disappear[i] += n;
        if (disappear[i] - appear[i] + 1 > res) res = disappear[i] - appear[i] + 1;
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &T[i]);
        next[i] = i % n + 1;
        prev[i] = (i - 2 + n) % n + 1;
    }
    build(1, 1, n);
    
    int LastAns = solve();
    printf("%d\n", LastAns);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (p) {
            x ^= LastAns;
            y ^= LastAns;
        }
        update(1, x, y);
        LastAns = solve();
        printf("%d\n", LastAns);
    }
    
    return 0;
}