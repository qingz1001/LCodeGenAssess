#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void longest_decreasing_subsequence(int* arr, int size, int* lis) {
    int len = 1;
    lis[0] = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < lis[len - 1]) {
            lis[len++] = arr[i];
        } else {
            int j = len - 1;
            while (lis[j] > arr[i]) {
                j--;
            }
            lis[j + 1] = arr[i];
        }
    }
}

void minimum_interceptors(int* arr, int size, int* lis) {
    int len = 1;
    lis[0] = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > lis[len - 1]) {
            lis[len++] = arr[i];
        } else {
            int j = len - 1;
            while (lis[j] < arr[i]) {
                j--;
            }
            lis[j] = arr[i];
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int* heights = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int* lis1 = (int*)malloc(n * sizeof(int));
    longest_decreasing_subsequence(heights, n, lis1);
    printf("%d\n", lis1[n - 1]);

    int* lis2 = (int*)malloc(n * sizeof(int));
    minimum_interceptors(heights, n, lis2);
    printf("%d\n", lis2[n - 1]);

    free(heights);
    free(lis1);
    free(lis2);
    return 0;
}