#include <stdio.h>
#include <stdlib.h>

int can_partition(int *arr, int n) {
    if (n % 2 != 0) return 0;
    int half = n / 2;
    for (int i = 0; i < half - 1; i++) {
        if (arr[i] >= arr[i + 1]) return 0;
    }
    for (int i = half; i < n - 1; i++) {
        if (arr[i] >= arr[i + 1]) return 0;
    }
    for (int i = 0; i < half - 1; i++) {
        for (int j = i + 1; j < half; j++) {
            if (arr[j] < arr[i]) return 0;
        }
    }
    for (int i = half; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) return 0;
        }
    }
    return 1;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        int *arr = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (can_partition(arr, N)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
        free(arr);
    }
    return 0;
}