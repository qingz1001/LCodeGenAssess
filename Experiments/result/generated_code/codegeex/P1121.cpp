#include <stdio.h>

#define MAXN 200005
#define LL long long

int n;
LL a[MAXN];
LL sum, max1, max2, min1, min2, ans;

LL max(LL a, LL b) {
    return a > b ? a : b;
}

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }

    max1 = max2 = -(LL)1e18;
    min1 = min2 = (LL)1e18;
    ans = -(LL)1e18;

    // 正向遍历，计算最大子段和
    LL curMax = 0;
    for (int i = 1; i <= n; i++) {
        curMax = max(curMax + a[i], a[i]);
        max1 = max(max1, curMax);
    }

    // 反向遍历，计算最大子段和
    curMax = 0;
    for (int i = n; i >= 1; i--) {
        curMax = max(curMax + a[i], a[i]);
        max2 = max(max2, curMax);
    }

    // 正向遍历，计算最小子段和
    LL curMin = 0;
    for (int i = 1; i <= n; i++) {
        curMin = min(curMin + a[i], a[i]);
        min1 = min(min1, curMin);
    }

    // 反向遍历，计算最小子段和
    curMin = 0;
    for (int i = n; i >= 1; i--) {
        curMin = min(curMin + a[i], a[i]);
        min2 = min(min2, curMin);
    }

    // 不跨环的情况
    ans = max(ans, max1 + max2);

    // 跨环的情况
    ans = max(ans, sum - min1 - min2);

    printf("%lld\n", ans);
    return 0;
}