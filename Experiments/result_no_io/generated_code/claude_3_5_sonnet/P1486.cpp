#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int* heap;
    int size;
} MaxHeap;

MaxHeap* createMaxHeap() {
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->heap = (int*)malloc(sizeof(int) * MAX_N);
    h->size = 0;
    return h;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MaxHeap* h, int index) {
    while (index > 0 && h->heap[(index - 1) / 2] < h->heap[index]) {
        swap(&h->heap[(index - 1) / 2], &h->heap[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(MaxHeap* h, int index) {
    int maxIndex = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->heap[left] > h->heap[maxIndex])
        maxIndex = left;
    if (right < h->size && h->heap[right] > h->heap[maxIndex])
        maxIndex = right;

    if (index != maxIndex) {
        swap(&h->heap[index], &h->heap[maxIndex]);
        heapifyDown(h, maxIndex);
    }
}

void insert(MaxHeap* h, int value) {
    h->heap[h->size] = value;
    heapifyUp(h, h->size);
    h->size++;
}

int extractMax(MaxHeap* h) {
    if (h->size == 0) return -1;
    int max = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return max;
}

int main() {
    int n, min, k, salary, adjust = 0, left = 0;
    char op;
    MaxHeap* heap = createMaxHeap();
    MaxHeap* temp = createMaxHeap();

    scanf("%d %d", &n, &min);

    while (n--) {
        scanf(" %c %d", &op, &k);
        
        switch(op) {
            case 'I':
                salary = k - adjust;
                if (salary >= min) {
                    insert(heap, salary);
                }
                break;
            case 'A':
                adjust += k;
                break;
            case 'S':
                adjust -= k;
                while (heap->size > 0 && heap->heap[0] + adjust < min) {
                    extractMax(heap);
                    left++;
                }
                break;
            case 'F':
                if (k > heap->size) {
                    printf("-1\n");
                } else {
                    while (temp->size < k) {
                        insert(temp, extractMax(heap));
                    }
                    printf("%d\n", temp->heap[0] + adjust);
                    while (temp->size > 0) {
                        insert(heap, extractMax(temp));
                    }
                }
                break;
        }
    }

    printf("%d\n", left);

    free(heap->heap);
    free(heap);
    free(temp->heap);
    free(temp);

    return 0;
}