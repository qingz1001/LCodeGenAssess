#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            if (mid == 0 || arr[mid - 1] != target) {
                return mid + 1; // 返回编号，从1开始
            } else {
                right = mid - 1;
            }
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int q;
        scanf("%d", &q);
        printf("%d ", binarySearch(arr, n, q));
    }
    
    free(arr);
    return 0;
}