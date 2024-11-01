#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXQ 25000

int n, Q;
int s[MAXN];
int sorted_s[MAXN];

void merge_sort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            sorted_s[k++] = arr[i++];
        } else {
            sorted_s[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        sorted_s[k++] = arr[i++];
    }
    while (j <= right) {
        sorted_s[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = sorted_s[k];
    }
}

int find_median(int start, int end) {
    int len = end - start + 1;
    if (len % 2 == 0) {
        return sorted_s[start + len / 2 - 1];
    } else {
        return sorted_s[start + len / 2];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }

    merge_sort(s, 0, n - 1);

    scanf("%d", &Q);
    int x = 0;
    for (int q = 0; q < Q; q++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a = (a + x) % n;
        b = (b + x) % n;
        c = (c + x) % n;
        d = (d + x) % n;

        if (a > b) a += n;
        if (c > d) c += n;

        if (a > c) {
            int temp = a; a = c; c = temp;
            temp = b; b = d; d = temp;
        }

        int median = find_median(a, d);
        printf("%d\n", median);
        x = median;
    }

    return 0;
}