#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000
#define MAX_M 200000
#define MAX_W 1000000

typedef long long ll;

ll w[MAX_N + 1];
ll v[MAX_N + 1];
ll l[MAX_M + 1];
ll r[MAX_M + 1];
ll y[MAX_M + 1];
ll prefix_w[MAX_W + 1];
ll prefix_v[MAX_W + 1];

ll sum_w[MAX_N + 1];
ll sum_v[MAX_N + 1];

ll n, m, s;

// 计算前缀和
void compute_prefix() {
    for (int i = 1; i <= n; i++) {
        sum_w[i] = sum_w[i - 1] + (w[i] >= W ? w[i] : 0);
        sum_v[i] = sum_v[i - 1] + (w[i] >= W ? v[i] : 0);
    }
}

// 计算给定W下的检验结果
ll calculate_y() {
    ll result = 0;
    for (int i = 1; i <= m; i++) {
        ll w_count = sum_w[r[i]] - sum_w[l[i] - 1];
        ll v_count = sum_v[r[i]] - sum_v[l[i] - 1];
        result += w_count * v_count;
    }
    return result;
}

// 二分查找最优W
ll binary_search() {
    ll left = 0, right = MAX_W;
    while (left < right) {
        ll mid = (left + right) / 2;
        W = mid;
        compute_prefix();
        ll y = calculate_y();
        if (abs(y - s) < abs(calculate_y() - s)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return abs(calculate_y() - s);
}

int main() {
    scanf("%lld %lld %lld", &n, &m, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &w[i], &v[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lld %lld", &l[i], &r[i]);
    }
    printf("%lld\n", binary_search());
    return 0;
}