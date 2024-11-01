#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200000

typedef long long ll;

int n, m;
ll s;
int w[MAXN], v[MAXN];
int l[MAXN], r[MAXN];
ll prefix_count[MAXN], prefix_value[MAXN];

ll calculate_y(int W) {
    ll y = 0;
    for (int i = 0; i < n; i++) {
        prefix_count[i + 1] = prefix_count[i] + (w[i] >= W);
        prefix_value[i + 1] = prefix_value[i] + (w[i] >= W ? v[i] : 0);
    }
    for (int i = 0; i < m; i++) {
        y += (prefix_count[r[i]] - prefix_count[l[i] - 1]) * (prefix_value[r[i]] - prefix_value[l[i] - 1]);
    }
    return y;
}

int main() {
    scanf("%d %d %lld", &n, &m, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    int left = 0, right = 1e6 + 1;
    ll min_diff = LLONG_MAX;

    while (left < right) {
        int mid = (left + right) / 2;
        ll y = calculate_y(mid);
        ll diff = llabs(y - s);
        if (diff < min_diff) {
            min_diff = diff;
        }
        if (y < s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", min_diff);
    return 0;
}