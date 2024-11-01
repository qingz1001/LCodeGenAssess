#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int Q;
    scanf("%d", &Q);
    int *m = (int *)malloc(Q * sizeof(int));
    for (int i = 0; i < Q; i++) {
        scanf("%d", &m[i]);
    }

    // 使用二分查找来找到每个 m 对应的位置
    for (int i = 0; i < Q; i++) {
        int left = 0, right = n - 1;
        int position = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (a[mid] == m[i]) {
                position = mid + 1; // 位置从1开始计数
                break;
            } else if (a[mid] < m[i]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (position == -1) {
            printf("0\n");
        } else {
            printf("%d\n", position);
        }
    }

    free(a);
    free(m);
    return 0;
}