#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findMedian(int *arr, int len) {
    qsort(arr, len, sizeof(int), compare);
    return arr[len / 2];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int result = a[0];
    for (int i = 0; i <= k; i++) {
        int median = findMedian(a, n - i);
        if (median > result) {
            result = median;
        }
    }

    printf("%d\n", result);
    free(a);
    return 0;
}