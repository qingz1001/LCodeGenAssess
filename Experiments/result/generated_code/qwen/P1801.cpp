#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (int*)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0 && pq->data[index] < pq->data[(index - 1) / 2]) {
        swap(&pq->data[index], &pq->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, pq->capacity * sizeof(int));
    }
    pq->data[pq->size++] = value;
    heapifyUp(pq, pq->size - 1);
}

int extractMin(PriorityQueue *pq) {
    int min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return min;
}

void heapifyDown(PriorityQueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->data[left] < pq->data[smallest]) {
        smallest = left;
    }

    if (right < pq->size && pq->data[right] < pq->data[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->data[index], &pq->data[smallest]);
        heapifyDown(pq, smallest);
    }
}

void freePriorityQueue(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int a[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    int u[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &u[i]);
    }

    PriorityQueue *pq = createPriorityQueue(m);

    for (int i = 0, j = 0; i < m || j < n;) {
        if (j < n && (i >= m || a[u[j] - 1] <= a[i])) {
            insert(pq, a[u[j] - 1]);
            j++;
        } else {
            printf("%d\n", extractMin(pq));
        }
    }

    freePriorityQueue(pq);
    return 0;
}