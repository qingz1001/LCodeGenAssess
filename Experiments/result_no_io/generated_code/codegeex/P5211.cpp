#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
#include <complex>

#define MAXN 200005
#define INF 0x3f3f3f3f

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int n, q;
int s[MAXN];

struct Node {
    int l, r, sum, lz;
} t[MAXN << 2];

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;
    if (l == r) {
        t[p].sum = s[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    t[p].sum = min(t[p << 1].sum, t[p << 1 | 1].sum);
}

void pushdown(int p) {
    if (t[p].lz) {
        t[p << 1].sum += t[p].lz;
        t[p << 1 | 1].sum += t[p].lz;
        t[p << 1].lz += t[p].lz;
        t[p << 1 | 1].lz += t[p].lz;
        t[p].lz = 0;
    }
}

void update(int p, int l, int r, int d) {
    if (l <= t[p].l && t[p].r <= r) {
        t[p].sum += d;
        t[p].lz += d;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) update(p << 1, l, r, d);
    if (r > mid) update(p << 1 | 1, l, r, d);
    t[p].sum = min(t[p << 1].sum, t[p << 1 | 1].sum);
}

int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) {
        return t[p].sum;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    int res = INF;
    if (l <= mid) res = min(res, query(p << 1, l, r));
    if (r > mid) res = min(res, query(p << 1 | 1, l, r));
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    build(1, 1, n);
    while (q--) {
        int op, l, r, d;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &d);
            update(1, l, r, d);
        } else {
            printf("%d\n", l + query(1, l, r) - s[l]);
        }
    }
    return 0;
}