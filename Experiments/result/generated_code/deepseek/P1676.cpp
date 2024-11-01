#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int isPossible(int *positions, int n, int m, int distance) {
    int cows = 1;
    int last_position = positions[0];
    for (int i = 1; i < n; i++) {
        if (positions[i] - last_position >= distance) {
            cows++;
            last_position = positions[i];
            if (cows >= m) return 1;
        }
    }
    return 0;
}

int maxMinDistance(int *positions, int n, int m) {
    qsort(positions, n, sizeof(int), compare);
    int left = 0, right = positions[n - 1] - positions[0];
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isPossible(positions, n, m, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *positions = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }
    printf("%d\n", maxMinDistance(positions, n, m));
    free(positions);
    return 0;
}