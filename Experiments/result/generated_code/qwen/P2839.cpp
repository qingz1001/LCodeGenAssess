#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXQ 25000

int arr[MAXN];
int sortedArr[MAXN * 2];

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (sortedArr[i] <= sortedArr[j]) {
            arr[k++] = sortedArr[i++];
        } else {
            arr[k++] = sortedArr[j++];
        }
    }
    while (i <= mid) {
        arr[k++] = sortedArr[i++];
    }
    while (j <= right) {
        arr[k++] = sortedArr[j++];
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        for (int i = left; i <= right; i++) {
            sortedArr[i] = arr[i];
        }
        merge(left, mid, right);
    }
}

int findMedian(int start, int end) {
    mergeSort(start, end);
    return arr[(start + end) / 2];
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &q);
    for (int qi = 0; qi < q; qi++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int x = qi > 0 ? ans : 0;
        int qa = (a + x) % n, qb = (b + x) % n, qc = (c + x) % n, qd = (d + x) % n;
        int minIndex = qa, maxIndex = qa;
        if (qb < minIndex) minIndex = qb;
        if (qc < minIndex) minIndex = qc;
        if (qd < minIndex) minIndex = qd;
        if (qb > maxIndex) maxIndex = qb;
        if (qc > maxIndex) maxIndex = qc;
        if (qd > maxIndex) maxIndex = qd;
        int median = findMedian(minIndex, maxIndex);
        printf("%d\n", median);
    }
    return 0;
}