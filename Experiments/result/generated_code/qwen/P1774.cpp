#include <stdio.h>
#include <stdlib.h>

int minSwaps(int arr[], int n) {
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
            swaps++;
            i--; // Check the swapped element with its previous elements
        }
    }
    return swaps;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", minSwaps(arr, n));
    free(arr);
    return 0;
}