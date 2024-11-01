#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, m;
int x[MAX_N];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int d) {
    int cows = 1, last = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] - last >= d) {
            cows++;
            last = x[i];
            if (cows >= m) return 1;
        }
    }
    return 0;
}

int binary_search() {
    int left = 0, right = x[n-1] - x[0];
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    qsort(x, n, sizeof(int), cmp);

    printf("%d\n", binary_search());

    return 0;
}