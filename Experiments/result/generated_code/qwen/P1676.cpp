#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int canPlaceCows(int positions[], int n, int m, int minDist) {
    int count = 1;
    int lastPosition = positions[0];
    for (int i = 1; i < n; i++) {
        if (positions[i] - lastPosition >= minDist) {
            count++;
            lastPosition = positions[i];
        }
    }
    return count >= m;
}

int aggressiveCows(int positions[], int n, int m) {
    qsort(positions, n, sizeof(int), compare);

    int low = 0;
    int high = positions[n-1] - positions[0];
    int result = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (canPlaceCows(positions, n, m, mid)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    printf("%d\n", aggressiveCows(positions, n, m));

    return 0;
}