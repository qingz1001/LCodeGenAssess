#include <stdio.h>

#define MAXN 1000001
#define MAXM 100001

int n, m;
long long a[MAXN];
int lazy[MAXN];

void update(int start, int end, int left, int right, int index, long long value) {
    if (left > end || right < start) return;
    if (start >= left && end <= right) {
        lazy[index] += value;
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, left, right, 2 * index, value);
    update(mid + 1, end, left, right, 2 * index + 1, value);
}

long long query(int start, int end, int index, int pos) {
    if (start == end) return a[start] + lazy[index];
    int mid = (start + end) / 2;
    if (pos <= mid) return query(start, mid, 2 * index, pos) + lazy[index];
    else return query(mid + 1, end, 2 * index + 1, pos) + lazy[index];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for (int i = 1; i <= m; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %lld", &x, &y);
            for (int k = 1; k * x <= n; ++k) update(1, n, k * x, k * x, 1, y);
        } else if (op == 2) {
            int j;
            scanf("%d", &j);
            printf("%lld\n", query(1, n, 1, j));
        }
    }
    return 0;
}