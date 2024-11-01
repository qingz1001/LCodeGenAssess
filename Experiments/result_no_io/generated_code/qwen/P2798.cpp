#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 20005

int n, k, m;
int a[MAXM], b[MAXM];
int Ti[MAXM], ti[MAXM];

int min(int x, int y) {
    return x < y ? x : y;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &a[i], &b[i], &Ti[i], &ti[i]);
    }

    quicksort(Ti, 0, m - 1);
    quicksort(ti, 0, m - 1);

    int result = 0;
    for (int i = 0; i < k; i++) {
        result = max(result, Ti[i]);
    }
    for (int i = k; i < m; i++) {
        result = max(result, ti[i]);
    }

    printf("%d\n", result);

    return 0;
}