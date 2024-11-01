#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int arr[MAXN];
int temp[MAXN];

void merge(int left, int mid, int right, int op) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if ((arr[i] <= arr[j] && op == 0) || (arr[i] >= arr[j] && op == 1)) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(int left, int right, int op) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid, op);
        mergeSort(mid + 1, right, op);
        merge(left, mid, right, op);
    }
}

int main() {
    int n, m, q, op, l, r;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &op, &l, &r);
        mergeSort(l - 1, r - 1, op);
    }
    scanf("%d", &q);
    printf("%d\n", arr[q - 1]);
    return 0;
}