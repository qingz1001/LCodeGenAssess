#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findPreviousPermutation(int arr[], int n) {
    // Step 1: Find the longest non-increasing suffix
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            break;
        }
    }

    // If the entire array is non-decreasing, it's already the smallest permutation
    if (i == -1) {
        printf("ERROR\n");
        return -1;
    }

    // Step 2: Find the largest element in the suffix that is smaller than arr[i]
    int j;
    for (j = n - 1; j > i; j--) {
        if (arr[j] < arr[i]) {
            break;
        }
    }

    // Step 3: Swap the found elements
    swap(&arr[i], &arr[j]);

    // Step 4: Reverse the suffix
    for (int start = i + 1, end = n - 1; start < end; start++, end--) {
        swap(&arr[start], &arr[end]);
    }

    return 0;
}

int main() {
    int N;
    scanf("%d", &N);
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    if (findPreviousPermutation(arr, N) != -1) {
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    free(arr);
    return 0;
}