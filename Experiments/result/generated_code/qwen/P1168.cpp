#include <stdio.h>
#include <stdlib.h>

void quickselect(int arr[], int left, int right, int k) {
    if (left == right)
        return;

    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[i];
    arr[i] = arr[right];
    arr[right] = temp;

    if (k == i)
        return;
    else if (k < i)
        quickselect(arr, left, i - 1, k);
    else
        quickselect(arr, i + 1, right, k);
}

int main() {
    int N;
    scanf("%d", &N);
    int *A = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < (N + 1) / 2; i++) {
        quickselect(A, 0, 2 * i, i);
        printf("%d\n", A[i]);
    }

    free(A);
    return 0;
}