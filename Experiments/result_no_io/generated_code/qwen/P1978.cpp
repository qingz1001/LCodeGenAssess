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

    int ans = 0;
    int i = 0;
    while (i < n) {
        ans++;
        long long current = arr[i];
        while (i < n && arr[i] <= current * k) {
            i++;
        }
    }

    printf("%d\n", ans);
    free(arr);
    return 0;
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}