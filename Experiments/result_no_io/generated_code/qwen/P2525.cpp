#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

int findPrevPermutation(int arr[], int n) {
    // Step 1: Find the largest index i such that arr[i] > arr[i + 1]
    int i;
    for (i = n - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
            break;
        }
    }

    // If no such index exists, then the array is sorted in ascending order
    if (i == -1) {
        printf("ERROR\n");
        return 0;
    }

    // Step 2: Find the largest index j greater than i such that arr[j] < arr[i]
    int j;
    for (j = n - 1; j > i; j--) {
        if (arr[j] < arr[i]) {
            break;
        }
    }

    // Step 3: Swap the value of arr[i] with that of arr[j]
    swap(&arr[i], &arr[j]);

    // Step 4: Reverse the sequence from arr[i + 1] up to and including the final element arr[n - 1]
    reverse(arr, i + 1, n - 1);

    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (!findPrevPermutation(arr, n)) {
        free(arr);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}