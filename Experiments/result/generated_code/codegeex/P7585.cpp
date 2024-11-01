#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// 检查是否可以满足嫉妒值为x
int check(int *arr, int m, int n, int x) {
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        cnt += (arr[i] + x - 1) / x; // 向上取整
    }
    return cnt <= n;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int *arr = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
    }

    // 将弹珠数量按降序排序
    qsort(arr, m, sizeof(int), compare);

    // 二分查找最小的嫉妒值
    int left = 1, right = arr[0];
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(arr, m, n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    free(arr);
    return 0;
}