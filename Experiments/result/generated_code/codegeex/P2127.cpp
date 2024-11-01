#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 对数组进行排序
    qsort(arr, n, sizeof(int), cmp);

    // 使用计数排序来计算最小代价
    int count[100001] = {0};
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    long long sum = 0;
    int pos = 0;
    for (int i = 1; i <= 100000; i++) {
        if (count[i] > 0) {
            for (int j = 0; j < count[i]; j++) {
                sum += arr[pos];
                pos++;
            }
        }
    }

    printf("%lld\n", sum);
    return 0;
}