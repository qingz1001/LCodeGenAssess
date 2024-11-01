#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

typedef struct {
    int *heap;
    int size;
    int capacity;
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap *h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (h->heap[index] < h->heap[parent]) {
            swap(&h->heap[index], &h->heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(Heap *h, int index) {
    while (2 * index + 1 < h->size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < h->size && h->heap[left] < h->heap[smallest]) {
            smallest = left;
        }
        if (right < h->size && h->heap[right] < h->heap[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(&h->heap[index], &h->heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert(Heap *h, int value) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->heap = (int *)realloc(h->heap, h->capacity * sizeof(int));
    }
    h->heap[h->size] = value;
    heapify_up(h, h->size);
    h->size++;
}

int extract_min(Heap *h) {
    if (h->size == 0) {
        return -1; // Error: heap is empty
    }
    int min_value = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    heapify_down(h, 0);
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

    Heap min_heap;
    min_heap.heap = (int *)malloc(MAX_N * sizeof(int));
    min_heap.size = 0;
    min_heap.capacity = MAX_N;

    int current_get_index = 0;
    int current_i = 0;

    for (int i = 0; i < m; i++) {
        insert(&min_heap, a[i]);

        while (current_get_index < n && u[current_get_index] == i + 1) {
            current_i++;
            printf("%d\n", min_heap.heap[current_i - 1]);
            current_get_index++;
        }
    }

    free(a);
    free(u);
    free(min_heap.heap);

    return 0;
}