#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 30000

typedef struct {
    int data[MAX_K];
    int size;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void insert(MinHeap *heap, int value) {
    if (heap->size == MAX_K) {
        return;
    }

    int i = heap->size;
    heap->data[i] = value;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[(i - 1) / 2], &heap->data[i]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap *heap) {
    if (heap->size == 0) {
        return -1;
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

void generateElements(MinHeap *heap, int k) {
    insert(heap, 1);

    for (int i = 0; i < k; i++) {
        int min = extractMin(heap);
        insert(heap, 2 * min + 1);
        insert(heap, 4 * min + 5);
    }
}

void removeDigits(char *number, int m) {
    int len = strlen(number);
    int stack[len];
    int top = -1;

    for (int i = 0; i < len; i++) {
        while (top >= 0 && m > 0 && stack[top] < number[i]) {
            top--;
            m--;
        }
        stack[++top] = number[i];
    }

    while (m > 0) {
        top--;
        m--;
    }

    for (int i = 0; i <= top; i++) {
        number[i] = stack[i];
    }
    number[top + 1] = '\0';
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    MinHeap heap = { .size = 0 };
    generateElements(&heap, k);

    int elements[k];
    for (int i = 0; i < k; i++) {
        elements[i] = extractMin(&heap);
    }

    char number[MAX_K * 5];
    int idx = 0;
    for (int i = k - 1; i >= 0; i--) {
        int temp = elements[i];
        while (temp > 0) {
            number[idx++] = (temp % 10) + '0';
            temp /= 10;
        }
    }
    number[idx] = '\0';

    printf("%s\n", number);
    removeDigits(number, m);
    printf("%s\n", number);

    return 0;
}