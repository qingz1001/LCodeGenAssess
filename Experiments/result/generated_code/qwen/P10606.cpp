#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, m;
long long a[MAXN];
int x[MAXN], y[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }

    long long cost = 0;
    for (int i = 1; i <= m; ++i) {
        int l = y[i], r = x[i] - 1;
        if (l > r) continue;
        int mid = (l + r) / 2;
        long long left_cost = 0, right_cost = 0;
        for (int j = 1; j <= mid; ++j) {
            left_cost += a[j];
        }
        for (int j = mid + 1; j <= r; ++j) {
            right_cost += a[j];
        }
        cost += (left_cost > right_cost ? left_cost : right_cost);
    }

    printf("%lld\n", cost);

    return 0;
}