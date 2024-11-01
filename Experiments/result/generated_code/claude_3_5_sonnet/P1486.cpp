#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int* data;
    int size;
} Heap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* h, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->data[left] > h->data[largest])
        largest = left;

    if (right < h->size && h->data[right] > h->data[largest])
        largest = right;

    if (largest != i) {
        swap(&h->data[i], &h->data[largest]);
        heapify(h, largest);
    }
}

void insert(Heap* h, int val) {
    h->size++;
    int i = h->size - 1;
    h->data[i] = val;

    while (i > 0 && h->data[(i - 1) / 2] < h->data[i]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMax(Heap* h) {
    if (h->size == 0) return -1;

    int max = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapify(h, 0);

    return max;
}

int main() {
    int n, min;
    scanf("%d %d", &n, &min);

    Heap heap;
    heap.data = (int*)malloc(MAX_N * sizeof(int));
    heap.size = 0;

    int adjust = 0, left = 0;

    for (int i = 0; i < n; i++) {
        char cmd;
        int k;
        scanf(" %c %d", &cmd, &k);

        switch (cmd) {
            case 'I':
                if (k - adjust >= min)
                    insert(&heap, k - adjust);
                break;
            case 'A':
                adjust += k;
                break;
            case 'S':
                adjust -= k;
                while (heap.size > 0 && heap.data[0] + adjust < min) {
                    extractMax(&heap);
                    left++;
                }
                break;
            case 'F':
                if (k > heap.size) {
                    printf("-1\n");
                } else {
                    Heap temp = heap;
                    int result;
                    for (int j = 0; j < k; j++) {
                        result = extractMax(&temp);
                    }
                    printf("%d\n", result + adjust);
                }
                break;
        }
    }

    printf("%d\n", left);

    free(heap.data);
    return 0;
}