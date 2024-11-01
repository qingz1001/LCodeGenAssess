#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void next_permutation(int *arr, int n) {
    int i, j;
    for (i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            for (j = n - 1; j > i; j--) {
                if (arr[j] > arr[i]) {
                    swap(&arr[i], &arr[j]);
                    break;
                }
            }
            for (j = i + 1; j < (n + i + 1) / 2; j++) {
                swap(&arr[j], &arr[n + i - j]);
            }
            return;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int fingers[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &fingers[i]);
    }

    while (m > 0) {
        next_permutation(fingers, n);
        m--;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", fingers[i]);
    }
    printf("\n");

    return 0;
}