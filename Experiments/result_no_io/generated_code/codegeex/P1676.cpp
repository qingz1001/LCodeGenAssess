#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    qsort(positions, n, sizeof(int), compare);

    int left = 1, right = positions[n-1] - positions[0], result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 1, last_position = positions[0];

        for (int i = 1; i < n; i++) {
            if (positions[i] - last_position >= mid) {
                count++;
                last_position = positions[i];
                if (count == m) {
                    result = mid;
                    break;
                }
            }
        }

        if (count >= m) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}