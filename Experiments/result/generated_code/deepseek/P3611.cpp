#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10000
#define MAXD 100000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min_k(int N, int T_max, int d[]) {
    int left = 1, right = N, mid, result = N;
    while (left <= right) {
        mid = (left + right) / 2;
        int heap[mid];
        for (int i = 0; i < mid; i++) {
            heap[i] = d[i];
        }
        qsort(heap, mid, sizeof(int), compare);
        int time = 0;
        int index = mid;
        while (index < N) {
            int min_time = heap[0];
            time += min_time;
            for (int i = 0; i < mid; i++) {
                heap[i] -= min_time;
            }
            qsort(heap, mid, sizeof(int), compare);
            heap[0] = d[index++];
            qsort(heap, mid, sizeof(int), compare);
        }
        time += heap[mid - 1];
        if (time <= T_max) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

int main() {
    int N, T_max;
    int d[MAXN];
    scanf("%d %d", &N, &T_max);
    for (int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }
    int result = min_k(N, T_max, d);
    printf("%d\n", result);
    return 0;
}