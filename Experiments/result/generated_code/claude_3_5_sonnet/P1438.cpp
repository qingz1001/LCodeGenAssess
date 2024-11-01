#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

long long a[MAXN];
long long lazy[MAXN * 4];
long long d[MAXN * 4];

void build(int node, int start, int end) {
    if (start == end) {
        lazy[node] = d[node] = 0;
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    lazy[node] = d[node] = 0;
}

void pushdown(int node, int start, int end) {
    if (lazy[node] == 0 && d[node] == 0) return;
    int mid = (start + end) / 2;
    lazy[node * 2] += lazy[node];
    lazy[node * 2 + 1] += lazy[node] + (mid - start + 1) * d[node];
    d[node * 2] += d[node];
    d[node * 2 + 1] += d[node];
    lazy[node] = d[node] = 0;
}

void update(int node, int start, int end, int l, int r, long long k, long long diff) {
    if (r < start || l > end) return;
    if (l <= start && end <= r) {
        lazy[node] += k + (start - l) * diff;
        d[node] += diff;
        return;
    }
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r, k, diff);
    update(node * 2 + 1, mid + 1, end, l, r, k, diff);
}

long long query(int node, int start, int end, int p) {
    if (start == end) return a[p] + lazy[node];
    pushdown(node, start, end);
    int mid = (start + end) / 2;
    if (p <= mid) return query(node * 2, start, mid, p);
    else return query(node * 2 + 1, mid + 1, end, p);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    build(1, 1, n);
    
    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int l, r;
            long long k, d;
            scanf("%d %d %lld %lld", &l, &r, &k, &d);
            update(1, 1, n, l, r, k, d);
        } else {
            int p;
            scanf("%d", &p);
            printf("%lld\n", query(1, 1, n, p));
        }
    }
    
    return 0;
}