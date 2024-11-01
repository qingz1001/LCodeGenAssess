#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int minLength(int *positions, int n, int m) {
    qsort(positions, n, sizeof(int), compare);

    int left = 0, right = positions[n - 1] - positions[0];
    while (left < right) {
        int mid = (left + right) / 2;
        int count = 1;
        int last = positions[0];

        for (int i = 1; i < n; i++) {
            if (positions[i] - last > mid) {
                count++;
                last = positions[i];
            }
        }

        if (count <= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int result = minLength(positions, n, m);
    printf("%d\n", result);

    return 0;
}