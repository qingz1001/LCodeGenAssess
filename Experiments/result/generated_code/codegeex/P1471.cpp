#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

double a[MAXN];
double sum[MAXN];
double lazy[MAXN];

void build(int l, int r, int idx) {
    if (l == r) {
        sum[idx] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, idx * 2);
    build(mid + 1, r, idx * 2 + 1);
    sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
}

void update(int l, int r, int idx, int ul, int ur, double k) {
    if (ul <= l && r <= ur) {
        lazy[idx] += k;
        sum[idx] += k * (r - l + 1);
        return;
    }
    int mid = (l + r) / 2;
    if (lazy[idx]) {
        sum[idx * 2] += lazy[idx] * (mid - l + 1);
        sum[idx * 2 + 1] += lazy[idx] * (r - mid);
        lazy[idx * 2] += lazy[idx];
        lazy[idx * 2 + 1] += lazy[idx];
        lazy[idx] = 0;
    }
    if (ul <= mid) update(l, mid, idx * 2, ul, ur, k);
    if (ur > mid) update(mid + 1, r, idx * 2 + 1, ul, ur, k);
    sum[idx] = sum[idx * 2] + sum[idx * 2 + 1];
}

double query(int l, int r, int idx, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sum[idx];
    }
    int mid = (l + r) / 2;
    double res = 0;
    if (lazy[idx]) {
        res += lazy[idx] * (mid - l + 1);
        res += query(l, mid, idx * 2, ql, qr);
        res += query(mid + 1, r, idx * 2 + 1, ql, qr);
        return res;
    }
    if (ql <= mid) res += query(l, mid, idx * 2, ql, qr);
    if (qr > mid) res += query(mid + 1, r, idx * 2 + 1, ql, qr);
    return res;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &a[i]);
    }
    build(1, n, 1);
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            double k;
            scanf("%d%d%lf", &x, &y, &k);
            update(1, n, 1, x, y, k);
        } else if (op == 2) {
            int x, y;
            scanf("%d%d", &x, &y);
            double ans = query(1, n, 1, x, y);
            printf("%.4lf\n", ans / (y - x + 1));
        } else if (op == 3) {
            int x, y;
            scanf("%d%d", &x, &y);
            double sum = query(1, n, 1, x, y);
            double avg = sum / (y - x + 1);
            double variance = 0;
            for (int i = x; i <= y; i++) {
                variance += (a[i] + lazy[i] - avg) * (a[i] + lazy[i] - avg);
            }
            printf("%.4lf\n", variance / (y - x + 1));
        }
    }
    return 0;
}