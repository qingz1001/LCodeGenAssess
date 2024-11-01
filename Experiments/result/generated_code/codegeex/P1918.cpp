#include <stdio.h>

int main() {
    int n, m, Q;
    scanf("%d", &n);
    int bottles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
    }
    scanf("%d", &Q);
    int queries[Q];
    for (int i = 0; i < Q; i++) {
        scanf("%d", &queries[i]);
    }

    // 对瓶子的数量进行排序，以便使用二分查找
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bottles[j] > bottles[j + 1]) {
                int temp = bottles[j];
                bottles[j] = bottles[j + 1];
                bottles[j + 1] = temp;
            }
        }
    }

    // 处理每个查询
    for (int i = 0; i < Q; i++) {
        int target = queries[i];
        // 使用二分查找找到最接近target的位置
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (bottles[mid] == target) {
                printf("%d\n", mid + 1);
                break;
            } else if (bottles[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (left > right) {
            printf("0\n");
        }
    }

    return 0;
}