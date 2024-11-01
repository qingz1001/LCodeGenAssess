#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(int *arr, int n) {
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    if (i < 0) {
        return 0;
    }
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }
    swap(&arr[i], &arr[j]);
    int l = i + 1, r = n - 1;
    while (l < r) {
        swap(&arr[l], &arr[r]);
        l++;
        r--;
    }
    return 1;
}

int main() {
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < M; i++) {
        next_permutation(arr, N);
    }

    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    return 0;
}