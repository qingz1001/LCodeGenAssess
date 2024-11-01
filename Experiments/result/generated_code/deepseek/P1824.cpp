#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int canPlaceCows(int *stalls, int n, int c, int distance) {
    int cowsPlaced = 1;
    int lastPosition = stalls[0];
    for (int i = 1; i < n; i++) {
        if (stalls[i] - lastPosition >= distance) {
            cowsPlaced++;
            lastPosition = stalls[i];
            if (cowsPlaced == c) {
                return 1;
            }
        }
    }
    return 0;
}

int maxDistance(int *stalls, int n, int c) {
    qsort(stalls, n, sizeof(int), compare);
    int left = 1, right = stalls[n - 1] - stalls[0];
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canPlaceCows(stalls, n, c, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    int *stalls = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &stalls[i]);
    }
    printf("%d\n", maxDistance(stalls, n, c));
    free(stalls);
    return 0;
}