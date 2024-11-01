#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int N, Tmax;
int durations[MAX_N];

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int simulate(int K) {
    int time = 0;
    int heap[MAX_N];
    int heap_size = 0;

    for (int i = 0; i < N; i++) {
        if (heap_size < K) {
            heap[heap_size++] = durations[i];
            qsort(heap, heap_size, sizeof(int), compare);
        } else {
            time = (time < heap[K-1]) ? heap[K-1] : time;
            heap[K-1] = time + durations[i];
            qsort(heap, K, sizeof(int), compare);
        }
    }

    for (int i = 0; i < heap_size; i++) {
        if (time < heap[i]) time = heap[i];
    }

    return time;
}

int binary_search() {
    int left = 1, right = N;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (simulate(mid) <= Tmax) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &Tmax);
    for (int i = 0; i < N; i++) {
        scanf("%d", &durations[i]);
    }

    int result = binary_search();
    printf("%d\n", result);

    return 0;
}