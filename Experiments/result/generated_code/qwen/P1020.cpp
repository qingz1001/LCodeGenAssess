#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int dp[MAXN];
int lis(int *heights, int n) {
    if (n == 0) return 0;
    for (int i = 0; i < n; i++) dp[i] = 1;
    int max_len = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (heights[i] > heights[j]) {
                dp[i] = dp[j] + 1;
                if (dp[i] > max_len) max_len = dp[i];
            }
        }
    }
    return max_len;
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
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
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
    int heights[MAXN];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int max_intercept = lis(heights, n);

    mergeSort(heights, 0, n - 1);
    int min_systems = 1;
    for (int i = 1; i < n; i++) {
        if (heights[i] != heights[i - 1]) {
            min_systems++;
        }
    }

    printf("%d\n%d\n", max_intercept, min_systems);

    return 0;
}