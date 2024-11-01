#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

// 定义最小堆结构
typedef struct {
    int size;
    int data[MAX_N];
} MinHeap;

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 最小堆的插入操作
void insert(MinHeap *heap, int value) {
    heap->data[heap->size] = value;
    int current = heap->size;
    while (current > 0 && heap->data[current] < heap->data[(current - 1) / 2]) {
        swap(&heap->data[current], &heap->data[(current - 1) / 2]);
        current = (current - 1) / 2;
    }
    heap->size++;
}

// 最小堆的删除最小值操作
int extractMin(MinHeap *heap) {
    int minValue = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest != current) {
            swap(&heap->data[current], &heap->data[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    return minValue;
}

int main() {
    int n;
    scanf("%d", &n);
    MinHeap heap = {0};
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        insert(&heap, a);
    }

    int totalCost = 0;
    while (heap.size > 1) {
        int first = extractMin(&heap);
        int second = extractMin(&heap);
        int cost = first + second;
        totalCost += cost;
        insert(&heap, cost);
    }

    printf("%d\n", totalCost);
    return 0;
}