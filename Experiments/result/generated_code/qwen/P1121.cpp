#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxSubarraySum(int arr[], int size) {
    int max_so_far = arr[0];
    int curr_max = arr[0];
    for (int i = 1; i < size; i++) {
        curr_max = MAX(arr[i], curr_max + arr[i]);
        max_so_far = MAX(max_so_far, curr_max);
    }
    return max_so_far;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max_sum = INT_MIN;
    int total_sum = 0;

    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
        arr[i] = -arr[i]; // Negate the array to find the minimum subarray sum
    }

    int min_subarray_sum = maxSubarraySum(arr, n);
    max_sum = total_sum + min_subarray_sum;

    if (max_sum == 0) {
        max_sum = maxSubarraySum(arr, n); // If all elements are negative, take the maximum single element
    }

    printf("%d\n", max_sum);

    free(arr);
    return 0;
}