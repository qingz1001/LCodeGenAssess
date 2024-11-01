#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    // 动态分配数组存储果子的数量
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 创建一个优先队列（小顶堆）
    int heapSize = n;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, heapSize, i);
    }

    long long totalCost = 0;
    while (heapSize > 1) {
        // 取出最小的两个数
        int min1 = extractMin(a, heapSize);
        int min2 = extractMin(a, --heapSize);

        // 合并这两个数并加入堆中
        int merged = min1 + min2;
        totalCost += merged;
        insert(a, heapSize, merged);
        heapSize++;
    }

    printf("%lld\n", totalCost);
    free(a);
    return 0;
}

// 维护小顶堆
void heapify(int *a, int heapSize, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && a[left] < a[smallest]) {
        smallest = left;
    }
    if (right < heapSize && a[right] < a[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        int temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        heapify(a, heapSize, smallest);
    }
}

// 从堆中取出最小元素
int extractMin(int *a, int &heapSize) {
    int min = a[0];
    a[0] = a[heapSize - 1];
    heapSize--;
    heapify(a, heapSize, 0);
    return min;
}

// 向堆中插入元素
void insert(int *a, int &heapSize, int value) {
    a[heapSize] = value;
    int i = heapSize;
    while (i > 0 && a[(i - 1) / 2] > a[i]) {
        int temp = a[i];
        a[i] = a[(i - 1) / 2];
        a[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}