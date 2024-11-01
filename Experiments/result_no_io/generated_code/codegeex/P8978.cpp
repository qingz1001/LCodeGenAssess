#include <stdio.h>
#include <stdlib.h>

#define MAXN 400005

int a[MAXN], n, k;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int x) {
    int cnt = 0;
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (a[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    int pivot = l;
    l = 1, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (a[mid] <= x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    int len = l - pivot + 1;
    if (len % 2 == 0) {
        if (len / 2 <= k) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if ((len - 1) / 2 <= k) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a + 1, n, sizeof(int), compare);
    int l = 0, r = 1000000000;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", l);
    return 0;
}