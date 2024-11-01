#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, m;
int a[MAXN];
int conditions[MAXN][2];

int min(int a, int b) {
    return a < b ? a : b;
}

void merge(int *arr, int l, int m, int r) {
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

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &conditions[i][0], &conditions[i][1]);
    }

    mergeSort(a, 0, n - 1);

    long long cost = 0;
    for (int i = 0; i < m; i++) {
        int x = conditions[i][0];
        int y = conditions[i][1];
        int idx = 0;
        while (idx < n && a[idx] < x) {
            idx++;
        }
        int left_cost = idx * x - sum(a, 0, idx - 1);
        int right_cost = sum(a, idx, n - 1) - (n - idx) * x;
        cost += min(left_cost, right_cost);
    }

    printf("%lld\n", cost);

    return 0;
}