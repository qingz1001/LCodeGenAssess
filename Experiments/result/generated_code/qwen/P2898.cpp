#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_Q 25000

int n, q;
int conditions[MAX_Q][3];

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int findConflict(int conditions[][3], int q) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < q; i++) {
        int l = conditions[i][0];
        int r = conditions[i][1];
        int x = conditions[i][2];

        mergeSort(arr + l - 1, 0, r - l);

        if (arr[l - 1] != x) {
            free(arr);
            return i + 1;
        }
    }

    free(arr);
    return 0;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &conditions[i][0], &conditions[i][1], &conditions[i][2]);
    }

    printf("%d\n", findConflict(conditions, q));

    return 0;
}