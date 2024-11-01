#include <stdio.h>
#include <stdlib.h>

// 定义最小堆结构
typedef struct {
    int *array;
    int size;
    int capacity;
} MinHeap;

// 初始化最小堆
MinHeap* initMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 交换堆中两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 插入元素到最小堆
void insert(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        return;
    }
    heap->array[heap->size] = value;
    int current = heap->size;
    heap->size++;

    while (current > 0 && heap->array[current] < heap->array[(current - 1) / 2]) {
        swap(&heap->array[current], &heap->array[(current - 1) / 2]);
        current = (current - 1) / 2;
    }
}

// 从最小堆中取出最小元素
int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    int min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;

        if (left < heap->size && heap->array[left] < heap->array[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->array[right] < heap->array[smallest]) {
            smallest = right;
        }
        if (smallest != current) {
            swap(&heap->array[current], &heap->array[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    return min;
}

int main() {
    int n;
    scanf("%d", &n);
    MinHeap* heap = initMinHeap(n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        insert(heap, a);
    }

    int totalCost = 0;
    while (heap->size > 1) {
        int first = extractMin(heap);
        int second = extractMin(heap);
        int cost = first + second;
        totalCost += cost;
        insert(heap, cost);
    }

    printf("%d\n", totalCost);

    free(heap->array);
    free(heap);
    return 0;
}