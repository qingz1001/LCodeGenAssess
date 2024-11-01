#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    int max_length = 1;
    int current_length = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i-1] + 1) {
            current_length++;
        } else if (arr[i] > arr[i-1] + 1) {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 1;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    printf("%d\n", max_length);

    free(arr);
    return 0;
}