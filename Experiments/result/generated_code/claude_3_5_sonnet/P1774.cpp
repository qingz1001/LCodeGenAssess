#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

long long merge_sort(int arr[], int temp[], int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long inversions = merge_sort(arr, temp, left, mid) + merge_sort(arr, temp, mid + 1, right);

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += mid - i + 1;
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = merge_sort(arr, temp, 0, n - 1);
    printf("%lld\n", result);

    free(arr);
    free(temp);
    return 0;
}