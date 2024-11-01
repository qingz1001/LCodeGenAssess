#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int *heap_max = (int *)malloc((N + 1) / 2 * sizeof(int));
    int *heap_min = (int *)malloc((N + 1) / 2 * sizeof(int));
    int size_max = 0, size_min = 0;

    for (int i = 0; i < N; i++) {
        if (size_max == 0 || A[i] <= heap_max[1]) {
            heap_max[++size_max] = A[i];
            int pos = size_max;
            while (pos > 1 && heap_max[pos] > heap_max[pos / 2]) {
                int tmp = heap_max[pos];
                heap_max[pos] = heap_max[pos / 2];
                heap_max[pos / 2] = tmp;
                pos /= 2;
            }
        } else {
            heap_min[++size_min] = A[i];
            int pos = size_min;
            while (pos > 1 && heap_min[pos] < heap_min[pos / 2]) {
                int tmp = heap_min[pos];
                heap_min[pos] = heap_min[pos / 2];
                heap_min[pos / 2] = tmp;
                pos /= 2;
            }
        }

        if (size_max - size_min > 1) {
            int tmp = heap_max[1];
            heap_max[1] = heap_max[size_max];
            heap_max[size_max--] = tmp;
            int pos = 1;
            while (pos * 2 <= size_max) {
                int max_pos = pos * 2;
                if (pos * 2 + 1 <= size_max && heap_max[max_pos] < heap_max[pos * 2 + 1]) {
                    max_pos = pos * 2 + 1;
                }
                if (heap_max[pos] < heap_max[max_pos]) {
                    int tmp = heap_max[pos];
                    heap_max[pos] = heap_max[max_pos];
                    heap_max[max_pos] = tmp;
                    pos = max_pos;
                } else {
                    break;
                }
            }
            heap_min[++size_min] = tmp;
            pos = size_min;
            while (pos > 1 && heap_min[pos] < heap_min[pos / 2]) {
                int tmp = heap_min[pos];
                heap_min[pos] = heap_min[pos / 2];
                heap_min[pos / 2] = tmp;
                pos /= 2;
            }
        } else if (size_min - size_max > 1) {
            int tmp = heap_min[1];
            heap_min[1] = heap_min[size_min];
            heap_min[size_min--] = tmp;
            int pos = 1;
            while (pos * 2 <= size_min) {
                int min_pos = pos * 2;
                if (pos * 2 + 1 <= size_min && heap_min[min_pos] > heap_min[pos * 2 + 1]) {
                    min_pos = pos * 2 + 1;
                }
                if (heap_min[pos] > heap_min[min_pos]) {
                    int tmp = heap_min[pos];
                    heap_min[pos] = heap_min[min_pos];
                    heap_min[min_pos] = tmp;
                    pos = min_pos;
                } else {
                    break;
                }
            }
            heap_max[++size_max] = tmp;
            pos = size_max;
            while (pos > 1 && heap_max[pos] > heap_max[pos / 2]) {
                int tmp = heap_max[pos];
                heap_max[pos] = heap_max[pos / 2];
                heap_max[pos / 2] = tmp;
                pos /= 2;
            }
        }

        if ((i + 1) % 2 == 1) {
            if (size_max > size_min) {
                printf("%d\n", heap_max[1]);
            } else {
                printf("%d\n", heap_min[1]);
            }
        }
    }

    free(A);
    free(heap_max);
    free(heap_min);
    return 0;
}