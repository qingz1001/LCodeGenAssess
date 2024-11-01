#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Request;

int compare(const void *a, const void *b) {
    Request *reqA = (Request *)a;
    Request *reqB = (Request *)b;
    if (reqA->end == reqB->end) {
        return reqA->start - reqB->start;
    }
    return reqA->end - reqB->end;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *capacities = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &capacities[i]);
    }

    Request *requests = (Request *)malloc(M * sizeof(Request));
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
        requests[i].start--; // Convert to 0-based index
        requests[i].end--;   // Convert to 0-based index
    }

    // Sort requests by end position
    qsort(requests, M, sizeof(Request), compare);

    // Use a max-heap to keep track of the maximum capacity used
    int *heap = (int *)malloc(N * sizeof(int));
    int heapSize = 0;

    // Process each request
    for (int i = 0; i < M; i++) {
        int start = requests[i].start;
        int end = requests[i].end;

        // Remove stalls that are no longer needed
        while (heapSize > 0 && heap[heapSize - 1] < start) {
            heapSize--;
        }

        // Check if adding this request exceeds any stall's capacity
        if (heapSize == 0 || capacities[heap[heapSize - 1]] > 0) {
            capacities[heap[heapSize]]--;
            heap[heapSize] = end;
            heapSize++;
        }

        // Maintain the heap property
        for (int j = heapSize / 2 - 1; j >= 0; j--) {
            int largest = j;
            int left = 2 * j + 1;
            int right = 2 * j + 2;

            if (left < heapSize && heap[left] > heap[largest]) {
                largest = left;
            }

            if (right < heapSize && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != j) {
                int temp = heap[j];
                heap[j] = heap[largest];
                heap[largest] = temp;
            }
        }
    }

    free(capacities);
    free(requests);
    free(heap);

    printf("%d\n", M - heapSize);
    return 0;
}