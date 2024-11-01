#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[100005];
    int ans = 0;
    int left = 0, right = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    while (right < n) {
        // 找到从right开始的最长的水瓶子区间
        while (right < n && a[right] == 0) {
            right++;
        }
        if (right == n) {
            break;
        }
        // 找到这个区间的左边界
        left = right;
        while (right < n && a[right] == 1) {
            right++;
        }
        // 吃掉这个区间
        ans++;
    }

    printf("%d\n", ans);
    return 0;
}