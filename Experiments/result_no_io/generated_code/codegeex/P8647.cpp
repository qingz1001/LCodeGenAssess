#include <stdio.h>

// 判断是否可以切出至少 k 块边长为 s 的正方形巧克力
int canCut(int n, int k, int s, int h[], int w[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += (h[i] / s) * (w[i] / s);
        if (count >= k) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int h[100001], w[100001];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &h[i], &w[i]);
    }

    // 二分查找最大边长
    int left = 1, right = 100001;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (canCut(n, k, mid, h, w)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", left);
    return 0;
}