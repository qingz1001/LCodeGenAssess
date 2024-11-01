#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

int next_permutation(int arr[], int n) {
    int i = n - 2;
    while (i >= 0 && arr[i] <= arr[i + 1]) {
        i--;
    }
    if (i < 0) {
        return 0; // 已经是第一个排列
    }
    int j = n - 1;
    while (arr[j] >= arr[i]) {
        j--;
    }
    swap(&arr[i], &arr[j]);
    reverse(arr, i + 1, n - 1);
    return 1;
}

int main() {
    int N;
    scanf("%d", &N);
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    if (!next_permutation(arr, N)) {
        printf("ERROR\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}