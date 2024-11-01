#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int check(int *x, int n, int c, int distance) {
    int cows = 1;
    int last = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] - last >= distance) {
            cows++;
            last = x[i];
            if (cows >= c) return 1;
        }
    }
    return 0;
}

int main() {
    int n, c;
    int x[MAX_N];

    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    qsort(x, n, sizeof(int), compare);

    int left = 0;
    int right = x[n-1] - x[0];
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(x, n, c, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);

    return 0;
}