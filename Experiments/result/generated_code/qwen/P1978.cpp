#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    long long *arr = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    // Sort the array
    qsort(arr, n, sizeof(long long), compare);

    int count = 0;
    long long last = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= last) {
            count++;
            last = arr[i] * k + 1;
        }
    }

    printf("%d\n", count);

    free(arr);
    return 0;
}

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}