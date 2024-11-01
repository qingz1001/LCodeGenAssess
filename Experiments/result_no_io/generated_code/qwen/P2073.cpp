#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int price;
    int beauty;
} Flower;

typedef struct {
    Flower *data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (Flower*)malloc(capacity * sizeof(Flower));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void destroyPriorityQueue(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void swap(Flower *a, Flower *b) {
    Flower temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    while (index > 0 && pq->data[(index - 1) / 2].price < pq->data[index].price) {
        swap(&pq->data[(index - 1) / 2], &pq->data[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->data[left].price > pq->data[largest].price) {
        largest = left;
    }

    if (right < pq->size && pq->data[right].price > pq->data[largest].price) {
        largest = right;
    }

    if (largest != index) {
        swap(&pq->data[index], &pq->data[largest]);
        heapifyDown(pq, largest);
    }
}

void insert(PriorityQueue *pq, Flower flower) {
    if (pq->size >= pq->capacity) {
        pq->capacity *= 2;
        pq->data = (Flower*)realloc(pq->data, pq->capacity * sizeof(Flower));
    }
    pq->data[pq->size++] = flower;
    heapifyUp(pq, pq->size - 1);
}

Flower extractMax(PriorityQueue *pq) {
    Flower max = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return max;
}

Flower extractMin(PriorityQueue *pq) {
    Flower min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return min;
}

int main() {
    int m;
    scanf("%d", &m);

    PriorityQueue *maxPQ = createPriorityQueue(MAX_N);
    PriorityQueue *minPQ = createPriorityQueue(MAX_N);
    int totalBeauty = 0;
    int totalPrice = 0;

    for (int i = 0; i < m; ++i) {
        int op;
        scanf("%d", &op);

        if (op == -1) {
            break;
        } else if (op == 1) {
            int w, c;
            scanf("%d %d", &w, &c);
            Flower flower = {c, w};
            if (!isEmpty(minPQ) && minPQ->data[0].price <= c) continue;
            insert(maxPQ, flower);
            insert(minPQ, flower);
            totalBeauty += w;
            totalPrice += c;
        } else if (op == 2) {
            if (!isEmpty(maxPQ)) {
                Flower maxFlower = extractMax(maxPQ);
                Flower minFlower = extractMin(minPQ);
                if (maxFlower.price != minFlower.price) {
                    printf("Error: Price mismatch\n");
                    exit(1);
                }
                totalBeauty -= maxFlower.beauty;
                totalPrice -= maxFlower.price;
            }
        } else if (op == 3) {
            if (!isEmpty(minPQ)) {
                Flower minFlower = extractMin(minPQ);
                Flower maxFlower = extractMax(maxPQ);
                if (minFlower.price != maxFlower.price) {
                    printf("Error: Price mismatch\n");
                    exit(1);
                }
                totalBeauty -= minFlower.beauty;
                totalPrice -= minFlower.price;
            }
        }
    }

    printf("%d %d\n", totalBeauty, totalPrice);

    destroyPriorityQueue(maxPQ);
    destroyPriorityQueue(minPQ);

    return 0;
}