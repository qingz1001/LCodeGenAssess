#include <stdio.h>
#include <stdlib.h>

int min_rotation(int *arr, int n) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int diff = arr[(i + k) % n] - arr[(j + k) % n];
        if (diff == 0) {
            k++;
        } else {
            if (diff > 0) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            if (i == j) {
                j++;
            }
            k = 0;
        }
    }
    return i < j ? i : j;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int start = min_rotation(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[(start + i) % n]);
    }
    printf("\n");

    free(arr);
    return 0;
}