#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void replaceWithMedian(int *arr, int start, int end) {
    qsort(arr + start, end - start + 1, sizeof(int), compare);
    int median = arr[(start + end) / 2];
    for (int i = start; i <= end; i++) {
        arr[i] = median;
    }
}

int findMaxMinAfterKOperations(int *arr, int n, int k) {
    if (k == 0) {
        return *arr;
    }
    int maxMin = arr[n - 1];
    for (int i = 0; i <= n - k; i++) {
        replaceWithMedian(arr, i, i + k);
        int currentMin = arr[i];
        for (int j = i + k + 1; j <= n; j += k + 1) {
            if (j + k >= n) {
                replaceWithMedian(arr, j, n - 1);
                currentMin = arr[j];
                break;
            } else {
                replaceWithMedian(arr, j, j + k);
                currentMin = arr[j];
            }
        }
        if (currentMin > maxMin) {
            maxMin = currentMin;
        }
    }
    return maxMin;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", findMaxMinAfterKOperations(arr, n, k));
    free(arr);
    return 0;
}