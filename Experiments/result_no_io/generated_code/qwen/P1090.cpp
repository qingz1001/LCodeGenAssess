#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minCost(int arr[], int n) {
    if (n <= 1) return 0;

    // Create a priority queue to store the elements of the array
    int cost = 0;
    while (n > 1) {
        // Extract the two smallest elements from the priority queue
        int first = arr[0];
        int second = arr[1];

        // Remove the two smallest elements and insert their sum back into the priority queue
        cost += first + second;
        arr[0] = first + second;
        arr[1] = 0; // Mark the second element as removed

        // Sort the array to maintain the order
        qsort(arr, n, sizeof(int), compare);

        // Reduce the size of the array by one
        n--;
    }

    return cost;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d\n", minCost(arr, n));

    return 0;
}