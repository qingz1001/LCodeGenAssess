#include <stdio.h>

int n, k;
int h[100005], w[100005];

// 计算边长为x的正方形巧克力能切出的块数
long long count(int x) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (h[i] / x) * (w[i] / x);
    }
    return ans;
}

int main() {
    // 读取输入
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &h[i], &w[i]);
    }

    // 二分查找最大边长
    int l = 1, r = 100000;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (count(mid) >= k) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    // 输出结果
    printf("%d\n", l);
    return 0;
}