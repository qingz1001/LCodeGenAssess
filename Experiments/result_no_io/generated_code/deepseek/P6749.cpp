#include <stdio.h>
#include <stdlib.h>

#define MAXN 30000

int a[MAXN];
int n, m;

long long merge_count(int arr[], int temp[], int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long count = merge_count(arr, temp, left, mid) + merge_count(arr, temp, mid + 1, right);

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += mid - i + 1;
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) arr[i] = temp[i];

    return count;
}

long long count_inversions(int arr[], int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    return merge_count(arr, temp, 0, size - 1);
}

void update_sequence(int l, int r, int x) {
    for (int i = l; i <= r; i++) {
        a[i] = x++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int op, l, r, x;
    for (int i = 0; i < m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d %d", &l, &r, &x);
            update_sequence(l - 1, r - 1, x);
        } else if (op == 2) {
            printf("%lld\n", count_inversions(a, n));
        }
    }

    return 0;
}