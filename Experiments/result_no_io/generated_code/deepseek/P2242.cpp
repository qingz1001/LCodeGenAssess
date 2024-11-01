#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *positions = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    qsort(positions, n, sizeof(int), compare);

    int left = 0, right = positions[n - 1] - positions[0];
    while (left < right) {
        int mid = left + (right - left) / 2;
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

    printf("%d\n", left);
    free(positions);
    return 0;
}