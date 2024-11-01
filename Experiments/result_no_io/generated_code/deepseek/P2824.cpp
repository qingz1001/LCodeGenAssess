#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int arr[MAXN];

void sort_interval(int l, int r, int op) {
    int temp[r - l + 1];
    for (int i = l; i <= r; i++) {
        temp[i - l] = arr[i];
    }
    if (op == 0) {
        qsort(temp, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
    } else {
        qsort(temp, r - l + 1, sizeof(int), (int (*)(const void *, const void *))strcmp);
        for (int i = 0; i < (r - l + 1) / 2; i++) {
            int t = temp[i];
            temp[i] = temp[r - l - i];
            temp[r - l - i] = t;
        }
    }
    for (int i = l; i <= r; i++) {
        arr[i] = temp[i - l];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        sort_interval(l, r, op);
    }
    scanf("%d", &q);
    printf("%d\n", arr[q]);
    return 0;
}