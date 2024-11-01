#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 400005

int n, k;
int a[MAX_N];
int sorted_a[MAX_N];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int x) {
    int ops = 0;
    int l = 1, r = 1;
    while (r <= n) {
        while (r <= n && sorted_a[r] - sorted_a[l] <= x) r++;
        ops += (r - l) / 2;
        l = r;
    }
    return ops <= k;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sorted_a[i] = a[i];
    }

    qsort(sorted_a + 1, n, sizeof(int), cmp);

    int left = 0, right = 1000000000;
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", left);
    return 0;
}