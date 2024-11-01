#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long minCost(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    long long cost = 0;
    for (int i = 0; i < n / 2; i++) {
        cost += (long long)(arr[i] + arr[n - i - 1]);
    }
    return cost;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%lld\n", minCost(arr, n));
    free(arr);
    return 0;
}