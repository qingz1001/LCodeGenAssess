#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

int can_partition(int *arr, int n) {
    if (n % 2 != 0) return 0;
    int half = n / 2;
    int *left = (int *)malloc(half * sizeof(int));
    int *right = (int *)malloc(half * sizeof(int));
    left[0] = arr[0];
    right[0] = arr[half];

    for (int i = 1; i < half; i++) {
        int pos_left = -1, pos_right = -1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > left[j]) pos_left = j + 1;
            if (arr[i + half] > right[j]) pos_right = j + 1;
        }
        if (pos_left == -1 || pos_right == -1) {
            free(left);
            free(right);
            return 0;
        }
        left[pos_left] = arr[i];
        right[pos_right] = arr[i + half];
    }

    free(left);
    free(right);
    return 1;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        int arr[MAX_N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (can_partition(arr, N)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    return 0;
}