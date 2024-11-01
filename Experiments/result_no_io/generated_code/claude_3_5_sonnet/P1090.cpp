#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001

// 优先队列（最小堆）的实现
typedef struct {
    int* heap;
    int size;
} PriorityQueue;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->heap[left] < pq->heap[smallest])
        smallest = left;

    if (right < pq->size && pq->heap[right] < pq->heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&pq->heap[i], &pq->heap[smallest]);
        heapify(pq, smallest);
    }
}

void insert(PriorityQueue* pq, int val) {
    int i = pq->size;
    pq->heap[i] = val;
    pq->size++;

    while (i > 0 && pq->heap[(i - 1) / 2] > pq->heap[i]) {
        swap(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(PriorityQueue* pq) {
    if (pq->size == 0) return -1;

    int min = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    return min;
}

int main() {
    int n, i;
    scanf("%d", &n);

    PriorityQueue pq;
    pq.heap = (int*)malloc(MAX_N * sizeof(int));
    pq.size = 0;

    for (i = 0; i < n; i++) {
        int fruit;
        scanf("%d", &fruit);
        insert(&pq, fruit);
    }

    long long total_effort = 0;

    while (pq.size > 1) {
        int a = extractMin(&pq);
        int b = extractMin(&pq);
        int sum = a + b;
        total_effort += sum;
        insert(&pq, sum);
    }

    printf("%lld\n", total_effort);

    free(pq.heap);
    return 0;
}