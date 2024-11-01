#include <stdio.h>
#include <stdlib.h>

#define MAXN 400005

int arr[MAXN];
int temp[MAXN];

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
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

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int getMedian(int start, int end) {
    mergeSort(start, end);
    return arr[(start + end) / 2];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = -1;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n - i; j++) {
            int median = getMedian(j, j + i - 1);
            for (int m = j; m < j + i; m++) {
                arr[m] = median;
            }
            int minVal = arr[0];
            for (int m = 1; m < n; m++) {
                if (arr[m] < minVal) {
                    minVal = arr[m];
                }
            }
            if (minVal > result) {
                result = minVal;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}