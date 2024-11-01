#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200000

typedef struct {
    int *heap;
    int size;
    int capacity;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->heap[parent] > heap->heap[index]) {
            swap(&heap->heap[parent], &heap->heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap *heap, int index) {
    while (2 * index + 1 < heap->size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->size && heap->heap[left] < heap->heap[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->heap[right] < heap->heap[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(&heap->heap[index], &heap->heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        return;
    }
    heap->heap[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

int extract_min(MinHeap *heap) {
    if (heap->size == 0) {
        return -1;
    }
    int min_value = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return min_value;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int *a = (int *)malloc(m * sizeof(int));
    int *u = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &u[i]);
    }

    MinHeap heap;
    heap.heap = (int *)malloc(MAX_SIZE * sizeof(int));
    heap.size = 0;
    heap.capacity = MAX_SIZE;

    int i = 0, j = 0;
    int current_get_index = 0;

    while (i < m || j < n) {
        if (j < n && i == u[j]) {
            printf("%d\n", heap.heap[0]);
            j++;
            current_get_index++;
        } else {
            insert(&heap, a[i]);
            i++;
        }
    }

    free(a);
    free(u);
    free(heap.heap);

    return 0;
}