#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

// 最小堆结构
typedef struct {
    int* heap;
    int size;
} MinHeap;

// 初始化最小堆
void initMinHeap(MinHeap* h, int capacity) {
    h->heap = (int*)malloc(sizeof(int) * (capacity + 1));
    h->size = 0;
}

// 向上调整
void heapifyUp(MinHeap* h, int index) {
    int temp = h->heap[index];
    while (index > 1 && temp < h->heap[index / 2]) {
        h->heap[index] = h->heap[index / 2];
        index /= 2;
    }
    h->heap[index] = temp;
}

// 向下调整
void heapifyDown(MinHeap* h, int index) {
    int temp = h->heap[index];
    int child;
    while (index * 2 <= h->size) {
        child = index * 2;
        if (child < h->size && h->heap[child + 1] < h->heap[child]) {
            child++;
        }
        if (temp <= h->heap[child]) break;
        h->heap[index] = h->heap[child];
        index = child;
    }
    h->heap[index] = temp;
}

// 插入元素
void insert(MinHeap* h, int value) {
    h->heap[++h->size] = value;
    heapifyUp(h, h->size);
}

// 删除并返回最小元素
int deleteMin(MinHeap* h) {
    int min = h->heap[1];
    h->heap[1] = h->heap[h->size--];
    heapifyDown(h, 1);
    return min;
}

int main() {
    int n, i;
    long long result = 0;
    MinHeap heap;

    scanf("%d", &n);
    initMinHeap(&heap, n);

    for (i = 0; i < n; i++) {
        int fruit;
        scanf("%d", &fruit);
        insert(&heap, fruit);
    }

    while (heap.size > 1) {
        int a = deleteMin(&heap);
        int b = deleteMin(&heap);
        int sum = a + b;
        result += sum;
        insert(&heap, sum);
    }

    printf("%lld\n", result);

    free(heap.heap);
    return 0;
}