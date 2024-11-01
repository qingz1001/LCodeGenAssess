#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int binary_search(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            while (mid > 0 && arr[mid - 1] == target) {
                mid--;
            }
            return mid + 1;
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

    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int query;
    for (int i = 0; i < m; i++) {
        scanf("%d", &query);
        int result = binary_search(arr, n, query);
        printf("%d ", result);
    }

    return 0;
}