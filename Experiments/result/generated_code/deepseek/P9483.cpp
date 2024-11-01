#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long weight;
    long long wear;
} BookStack;

typedef struct {
    BookStack *stacks;
    int size;
} MinHeap;

void swap(BookStack *a, BookStack *b) {
    BookStack temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->stacks[left].weight < heap->stacks[smallest].weight)
        smallest = left;

    if (right < heap->size && heap->stacks[right].weight < heap->stacks[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->stacks[idx], &heap->stacks[smallest]);
        heapify(heap, smallest);
    }
}

void insert(MinHeap *heap, BookStack stack) {
    int i = heap->size;
    heap->stacks[i] = stack;
    heap->size++;

    while (i != 0 && heap->stacks[(i - 1) / 2].weight > heap->stacks[i].weight) {
        swap(&heap->stacks[i], &heap->stacks[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

BookStack extractMin(MinHeap *heap) {
    if (heap->size == 1) {
        heap->size--;
        return heap->stacks[0];
    }

    BookStack root = heap->stacks[0];
    heap->stacks[0] = heap->stacks[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

long long minCostToMergeBooks(int n, long long weights[]) {
    MinHeap heap;
    heap.stacks = (BookStack *)malloc(n * sizeof(BookStack));
    heap.size = 0;

    for (int i = 0; i < n; i++) {
        BookStack stack = {weights[i], 0};
        insert(&heap, stack);
    }

    long long totalCost = 0;

    while (heap.size > 1) {
        BookStack first = extractMin(&heap);
        BookStack second = extractMin(&heap);

        long long newWeight = first.weight + second.weight;
        long long newWear = 2 * (first.wear > second.wear ? first.wear : second.wear) + 1;
        long long cost = newWeight + newWear;

        totalCost += cost;

        BookStack newStack = {newWeight, newWear};
        insert(&heap, newStack);
    }

    free(heap.stacks);
    return totalCost;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        long long weights[n];
        for (int i = 0; i < n; i++) {
            scanf("%lld", &weights[i]);
        }

        printf("%lld\n", minCostToMergeBooks(n, weights));
    }

    return 0;
}