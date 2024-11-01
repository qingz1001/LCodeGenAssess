#include <stdio.h>
#include <string.h>

void min_rotation(int *arr, int n) {
    int min_index = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[(min_index + i) % n]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    min_rotation(arr, n);
    return 0;
}