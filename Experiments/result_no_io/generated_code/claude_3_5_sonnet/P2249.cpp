#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

int a[MAX_N];

int binary_search(int *arr, int left, int right, int target) {
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
    int n, m, q;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &q);
        int result = binary_search(a, 0, n - 1, q);
        printf("%d ", result);
    }

    return 0;
}