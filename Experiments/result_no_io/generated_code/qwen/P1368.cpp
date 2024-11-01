#include <stdio.h>
#include <string.h>

void min_rotation(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j + n - i < n && arr[j] == arr[j + n - i]) {
            j++;
        }
        if (j + n - i >= n || arr[i] < arr[j + n - i]) {
            printf("%d ", arr[i]);
        } else {
            printf("%d ", arr[j + n - i]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    min_rotation(arr, n);
    return 0;
}