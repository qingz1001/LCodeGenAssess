#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll n, m, t;
ll a[500005], b[500005];
ll sum[500005];

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return (*(ll*)a - *(ll*)b);
}

int main() {
    // 读取输入
    scanf("%lld %lld %lld", &n, &m, &t);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (ll i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    // 对a和b进行排序
    qsort(a, n, sizeof(ll), cmp);
    qsort(b, m, sizeof(ll), cmp);

    // 计算前缀和
    sum[0] = 0;
    for (ll i = 1; i <= n; i++) {
        sum[i] = (sum[i-1] + a[i-1]) % MOD;
    }

    ll result = 0;
    for (ll i = 0; i < m; i++) {
        ll max_val = (i < t) ? b[i] : b[t-1];
        ll min_val = (i > 0) ? b[i-1] : 1;
        ll count = (i < t) ? i + 1 : t;

        // 计算每个位置的贡献
        ll contribution = (count * (max_val + min_val) * (max_val - min_val + 1) / 2) % MOD;
        contribution = (contribution - (sum[n] * (max_val - min_val + 1) % MOD)) % MOD;
        contribution = (contribution + MOD) % MOD;

        // 累加结果
        result = (result + contribution) % MOD;
    }

    // 输出结果
    printf("%lld\n", result);
    return 0;
}