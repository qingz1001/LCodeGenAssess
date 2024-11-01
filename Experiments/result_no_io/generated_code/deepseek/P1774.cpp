#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int arr[MAXN];
int temp[MAXN];

long long merge_and_count(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += (mid - i + 1);
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

    return count;
}

long long merge_sort_and_count(int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long count = 0;

    count += merge_sort_and_count(left, mid);
    count += merge_sort_and_count(mid + 1, right);
    count += merge_and_count(left, mid, right);

    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long ans = merge_sort_and_count(0, n - 1);
    printf("%lld\n", ans);

    return 0;
}