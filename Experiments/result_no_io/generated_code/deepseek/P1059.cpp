#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    scanf("%d", &N);
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    qsort(arr, N, sizeof(int), compare);

    // Remove duplicates
    int *unique_arr = (int *)malloc(N * sizeof(int));
    int unique_count = 0;
    unique_arr[unique_count++] = arr[0];
    for (int i = 1; i < N; i++) {
        if (arr[i] != arr[i - 1]) {
            unique_arr[unique_count++] = arr[i];
        }
    }

    // Output the result
    printf("%d\n", unique_count);
    for (int i = 0; i < unique_count; i++) {
        printf("%d ", unique_arr[i]);
    }
    printf("\n");

    free(arr);
    free(unique_arr);
    return 0;
}