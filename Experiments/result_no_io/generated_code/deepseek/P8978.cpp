#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findMedian(int *arr, int l, int r) {
    int len = r - l + 1;
    int mid = l + (len - 1) / 2;
    return arr[mid];
}

int canAchieve(int *arr, int n, int k, int target) {
    int operations = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < target) {
            int j = i;
            while (j < n && arr[j] < target) j++;
            operations += (j - i + 1) / 2;
            i = j;
        }
    }
    return operations <= k;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int low = a[0], high = a[n - 1];
    while (low < high) {
        int mid = low + (high - low + 1) / 2;
        if (canAchieve(a, n, k, mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", low);

    free(a);
    return 0;
}