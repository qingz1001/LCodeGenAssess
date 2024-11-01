#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int l, int r, int op) {
    if (op == 0) {
        qsort(arr + l - 1, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
    } else {
        qsort(arr + l - 1, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
        for (int i = l; i <= r; i++) {
            arr[i - 1] = -arr[i - 1];
        }
        qsort(arr + l - 1, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
        for (int i = l; i <= r; i++) {
            arr[i - 1] = -arr[i - 1];
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        sort(arr, l, r, op);
    }
    int q;
    scanf("%d", &q);
    printf("%d\n", arr[q - 1]);
    free(arr);
    return 0;
}